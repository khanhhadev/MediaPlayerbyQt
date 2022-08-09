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

    setCurrentIndex(-1);
    readBackup();
}

//get list of song from directory path
void MediaData::getURLList(QUrl path)
{
    QDir directory(path.toLocalFile());
    QStringList names  = directory.entryList(QStringList() << "*.mp3",QDir::Files);
    mSongList = names;
    emit songListChanged();
}

//return mDirectory path
QString MediaData::getDirectory() const
{
    return mDirectory;
}

//set mDirectory path
void MediaData::setDirectory(QString dir)
{
    if (dir != mDirectory)
    {
        mDirectory = dir;
        emit directoryChanged();
    }
}

//directoryChanged event handler
void MediaData::onDirectoryChanged()
{
    getURLList(mDirectory);
    setCurrentIndex(-1);
    writeBackup();
}

//directory changed from browser dialog event handler
void MediaData:: onChangingDirectory(QString path)
{
    setDirectory(path);
}

//return list of song urls in playlist
QStringList MediaData::getSongList() const
{
    return mSongList;
}

//change song list
void MediaData::setSongList(const QStringList newList)
{
    if(newList != mSongList)
    {
        mSongList = newList;
        emit songListChanged();
    }
}

//songListChanged event handler
void MediaData::onSongListChanged()
{
    setCurrentIndex(-1);
}

//return index of current song in playlist
int MediaData::getCurrentIndex() const
{
    return mCurrentIndex;
}

//set currentindex as index of currentsong of playlist
void MediaData::setCurrentIndex(const int currentindex)
{
    if (currentindex != mCurrentIndex)
    {
        mCurrentIndex = currentindex;
        emit currentIndexChanged(mCurrentIndex);
    }
}

//currentIndexChanged event handler
void MediaData::onCurrentIndexChanged()
{
    if (mSongList.count() > 0)
        emit sourceChanged(mDirectory + "/" + mSongList.at(mCurrentIndex));
    qDebug() << __FUNCTION__ << mCurrentIndex;
}

//move to next song in playlist
void MediaData::nextSong()
{
    if (mCurrentIndex < mSongList.count() - 1)
    {
        setCurrentIndex(mCurrentIndex+1);
        emit sourceChanged(mDirectory + "/" + mSongList.at(mCurrentIndex));
    } else
    {
        emit endOfList();
        emit sourceChanged("");
    }
}

//read back-up directory path from AppData.txt file
void MediaData::readBackup()
{
    QUrl path = mDataFileLocation;
    QDir dir(path.toLocalFile());
    if (!dir.exists()) dir.mkpath(".");
    QFile DataFile(mDataFileLocation + "/AppData.txt");
    if (DataFile.open(QIODevice::ReadWrite))
    {
        QString line = DataFile.readLine();
        if (line != "") setDirectory(line);
        else setDirectory(mDataFileLocation);
        DataFile.close();
    }
}

//wrire back-up directory path to AppData.txt file
void MediaData::writeBackup()
{
    QFile DataFile(mDataFileLocation + "/AppData.txt");
    qDebug() << "write" << mDirectory;
    if (DataFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&DataFile);
        stream << QString(mDirectory);
        DataFile.flush();
        DataFile.close();
        qDebug() << "writed" << mDirectory;
    }
}
