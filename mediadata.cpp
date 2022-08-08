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

    connect(this, &MediaData::directoryChanged,
            this, &MediaData::onDirectoryChanged);

    connect(this, &MediaData::currentIndexChanged,
            this, &MediaData::onCurrentIndexChanged);

    QDir dir(mDataFileLocation);
    if (!dir.exists()) dir.mkpath(".");
    QFile FileDemo(mDataFileLocation + "/AppData.txt");
    if (FileDemo.open(QIODevice::ReadWrite))
    {
        QByteArray line = FileDemo.readLine();
        if (line != "") setDirectory(line);
        else setDirectory(mDataFileLocation);
        FileDemo.close();
    }
    emit directoryChanged();
    qDebug() << __FUNCTION__ << mDirectory;
    //changeDirectory();
}

void MediaData::getURLList(QUrl path)
{
    QDir directory(path.toLocalFile());
    QStringList names  = directory.entryList(QStringList() << "*.mp3" /*<< "*.mp4"*/,QDir::Files);
    if (mSongList != names)
    {
        mSongList = names;
        emit songListChanged();
    }
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
    QFile FileDemo(mDataFileLocation + "/AppData.txt");
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
    setDirectory(path);
    emit directoryChanged();
    qDebug() << __FUNCTION__ << mDirectory;
}

void MediaData::nextSong()
{
    if (mCurrentIndex < mSongList.count() - 1)
    {
        setCurrentIndex(mCurrentIndex+1);
        emit sourceChanged(mDirectory + "/" + mSongList.at(mCurrentIndex));
    }
}

void MediaData::onSongListChanged()
{
    setCurrentIndex(-1);
}

void MediaData::onCurrentIndexChanged()
{
    emit sourceChanged(mDirectory + "/" + mSongList.at(mCurrentIndex));
}
