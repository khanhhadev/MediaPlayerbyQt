#include "mediadata.h"
#include <QDir>
#include <QDebug>
#include <QUrl>
#include <QFileDialog>
#include <QFile>
#include <QStandardPaths>
#include <QIODevice>

MediaData::MediaData(QObject *parent)
    : QObject{parent}
{
    mDataFileLocation = QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString() + "/MusicPlayer/AppData.txt";
    connect(this, &MediaData::directoryChanged,
            this, &MediaData::onDirectoryChanged);

    connect(this, &MediaData::currentIndexChanged,
            this, &MediaData::onCurrentIndexChanged);
    mDirectory = QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
//    QFile FileDemo(mDataFileLocation);
//    if (FileDemo.open(QIODevice::ReadWrite))
//    {
//        QByteArray line = FileDemo.readLine();
//        if (line != "") mDirectory = line;
//        else mDirectory = QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
//        FileDemo.close();
//    }
    emit directoryChanged();
    qDebug() << __FUNCTION__ << mDirectory;
    //changeDirectory();
}

void MediaData::getURLList(QUrl path)
{
    QDir directory(path.toLocalFile());
    QStringList names  = directory.entryList(QStringList() << "*.mp3" << "*.mp4",QDir::Files);
    mSongList = names;
    emit songListChanged();
    qDebug() << __FUNCTION__ << mDirectory;
    qDebug() << __FUNCTION__ << mSongList;
}

void MediaData::setDirectory(QString dir)
{
    if (dir != mDirectory)
    {
        mDirectory = dir;
        emit directoryChanged();
    }
}

QString MediaData::getDirectory() const
{
    return mDirectory;
}

void MediaData::onDirectoryChanged()
{
    getURLList(mDirectory);
    QFile FileDemo(mDataFileLocation);
    if (FileDemo.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&FileDemo);
        stream << mDirectory;
        FileDemo.flush();
        FileDemo.close();
        qDebug() << "writed" << mDirectory;
    }
    qDebug() << __FUNCTION__ << mDirectory;
    qDebug() << __FUNCTION__ << mSongList;
}

void MediaData::setSongList(const QStringList newList)
{
    if(newList != mSongList)
    {
        mSongList = newList;
        emit songListChanged();
    }
}

QStringList MediaData::getSongList() const
{
    return mSongList;
}

int MediaData::getCurrentIndex() const
{
    return mCurrentIndex;
}

void MediaData::setCurrentIndex(const int currentindex)
{
    if (currentindex != mCurrentIndex)
    {
        mCurrentIndex = currentindex;
        emit currentIndexChanged(mCurrentIndex);
    }
}

QString MediaData::getCurrentDirectory()
{
    return mDirectory;
}

void MediaData:: onChangingDirectory(QString path)
{
    mDirectory = path;
    emit directoryChanged();
    qDebug() << __FUNCTION__ << mDirectory;
}

void MediaData::onSongListChanged()
{
    qDebug() << __FUNCTION__;
}

void MediaData::onCurrentIndexChanged(int currentindex)
{
    qDebug() << __FUNCTION__;
    emit sourceChanged(mDirectory + "/" + mSongList.at(currentindex));
}
