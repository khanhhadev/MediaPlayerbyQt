#include "mediadatalist.h"
#include <QDir>
#include <QDebug>
#include <QUrl>
#include <QFileDialog>
#include <QFile>
#include <QStandardPaths>
#include <QIODevice>


MediaDataList::MediaDataList(QObject *parent)
    : QAbstractListModel(parent)
{
    mRoleNames[SourceRole] = "source";
    mRoleNames[NameRole] = "name";
    mRoleNames[AlbumTitleRole] = "album";
    mRoleNames[ContributingArtistRole] = "artist";
    mRoleNames[DateRole] = "date";
}

int MediaDataList::count() const
{
    return mData.length();
}

int MediaDataList::rowCount(const QModelIndex &parent = QModelIndex()) const
{
    if (parent.isValid()) return 0;
    return count();
}

QVariant MediaDataList::data(const QModelIndex &index, int role) const
{

    if(index.isValid() == false) return QVariant();
    //if(index.row() < 0 || index.row() >= count()) return QVariant();
    qDebug() << __FUNCTION__ << mData.at(index.row()).getValue(role);
    return mData.at(index.row()).getValue(role);

}

//QModelIndex MediaDataList::index(int row, int column = 0, const QModelIndex &parent) const
//{
//    return QModelIndex(index);
//}

//void MediaDataList::addNewFolder(const QUrl directorypath)
//{

//    emit songListChanged();
//    qDebug() << __FUNCTION__ << directorypath << sourcelist;
//}

void MediaDataList::addNewFiles(const MediaDataItem &file)
{
    auto itr = std::find(mData.begin(), mData.end(), file);
    if (itr == mData.end())
    {
        beginInsertRows(QModelIndex(), count(), count());
        mData.append(file);
        endInsertRows();
    }
}

void MediaDataList::addNewFiles(const QList<MediaDataItem> &list)
{
    for (MediaDataItem item : list)
    {
        addNewFiles(item);
    }
}

MediaDataItem MediaDataList::at(int row)
{
    return mData.at(row);
}

void MediaDataList::clear()
{
    while (count() > 0)
    {
        beginRemoveRows(QModelIndex(), 0, 0);
        mData.removeAt(0);
        endRemoveRows();
    }
}

void MediaDataList::sortList(bool asc)
{
    qDebug() << __FUNCTION__ << mData;
    std::sort(mData.begin(), mData.end()
               /*[=](const MediaDataItem& item1, const MediaDataItem& item2) ->  bool
                {return item1 > item2;}*/
    );
    emit layoutChanged();
    qDebug() << __FUNCTION__ << mData ;
}

QHash<int, QByteArray> MediaDataList::roleNames() const
{
    return mRoleNames;
}

//MediaDataList::MediaDataList(QObject *parent)
//    : QObject{parent}
//{
//    connect(this, &MediaDataList::directoryChanged,
//            this, &MediaDataList::onDirectoryChanged);

//    connect(this, &MediaDataList::currentIndexChanged,
//            this, &MediaDataList::onCurrentIndexChanged);

//    setCurrentIndex(-1);
//    readBackup();
//}

////get list of song from directory path
//void MediaDataList::getURLList(QUrl path)
//{
//    QDir directory(path.toLocalFile());
//    QStringList names  = directory.entryList(QStringList() << "*.mp3",QDir::Files);
//    mSongList = names;
//    emit songListChanged();
//}

////return mDirectory path
//QString MediaDataList::getDirectory() const
//{
//    return mDirectory;
//}

////set mDirectory path
//void MediaDataList::setDirectory(QString dir)
//{
//    if (dir != mDirectory)
//    {
//        mDirectory = dir;
//        emit directoryChanged();
//    }
//}

////directoryChanged event handler
//void MediaDataList::onDirectoryChanged()
//{
//    getURLList(mDirectory);
//    setCurrentIndex(-1);
//    writeBackup();
//}

////directory changed from browser dialog event handler
//void MediaDataList:: onChangingDirectory(QString path)
//{
//    setDirectory(path);
//}

////return list of song urls in playlist
//QStringList MediaDataList::getSongList() const
//{
//    return mSongList;
//}

////change song list
//void MediaDataList::setSongList(const QStringList newList)
//{
//    if(newList != mSongList)
//    {
//        mSongList = newList;
//        emit songListChanged();
//    }
//}

////songListChanged event handler
//void MediaDataList::onSongListChanged()
//{
//    setCurrentIndex(-1);
//}

////return index of current song in playlist
//int MediaDataList::getCurrentIndex() const
//{
//    return mCurrentIndex;
//}

////set currentindex as index of currentsong of playlist
//void MediaDataList::setCurrentIndex(const int currentindex)
//{
//    if (currentindex != mCurrentIndex)
//    {
//        mCurrentIndex = currentindex;
//        emit currentIndexChanged(mCurrentIndex);
//    }
//}

////currentIndexChanged event handler
//void MediaDataList::onCurrentIndexChanged()
//{
//    if (mSongList.count() > 0)
//        emit sourceChanged(mDirectory + "/" + mSongList.at(mCurrentIndex));
//    qDebug() << __FUNCTION__ << mCurrentIndex;
//}

////move to next song in playlist
//void MediaDataList::nextSong()
//{
//    if (mCurrentIndex < mSongList.count() - 1)
//    {
//        setCurrentIndex(mCurrentIndex+1);
//        emit sourceChanged(mDirectory + "/" + mSongList.at(mCurrentIndex));
//    } else
//    {
//        emit endOfList();
//        emit sourceChanged("");
//    }
//}

////read back-up directory path from AppData.txt file
//void MediaDataList::readBackup()
//{
//    QUrl path = mDataFileLocation;
//    QDir dir(path.toLocalFile());
//    if (!dir.exists()) dir.mkpath(".");
//    QFile DataFile(mDataFileLocation + "/AppData.txt");
//    if (DataFile.open(QIODevice::ReadWrite))
//    {
//        QString line = DataFile.readLine();
//        if (line != "") setDirectory(line);
//        else setDirectory(mDataFileLocation);
//        DataFile.close();
//    }
//}

////wrire back-up directory path to AppData.txt file
//void MediaDataList::writeBackup()
//{
//    QFile DataFile(mDataFileLocation + "/AppData.txt");
//    qDebug() << "write" << mDirectory;
//    if (DataFile.open(QIODevice::ReadWrite | QIODevice::Text))
//    {
//        QTextStream stream(&DataFile);
//        stream << QString(mDirectory);
//        DataFile.flush();
//        DataFile.close();
//        qDebug() << "writed" << mDirectory;
//    }
//}
