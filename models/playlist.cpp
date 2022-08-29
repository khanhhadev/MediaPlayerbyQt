#include <QDebug>
//#include <QFileDialog>
#include <QFile>
//#include <QStandardPaths>

#include "models/playlist.h"

PlayList::PlayList(QObject *parent)
    : QAbstractListModel(parent)
{
    mRoleNames[SourceRole] = "source";
    mRoleNames[NameRole] = "name";
    mRoleNames[AlbumTitleRole] = "album";
    mRoleNames[ContributingArtistRole] = "artist";
    mRoleNames[ImageRole] = "eimage";
    mRoleNames[LoveRole] = "love";
}

int PlayList::count() const
{
    switch (mMode) {
    case PLAYLIST:
        return mData.length();
    case ARTISTLIST:
    {
        if (mArtist.length() == 0) return 0;
        return mArtist.at(mCurrentArtist).count();
    }
    case ALBUMLIST:
    {
        if (mAlbum.length() == 0) return 0;
        return mAlbum.at(mCurrentAlbum).count();
    }
    case MYLIST:
        return mFavourite.length();
    default:
        return 0;
    }
}

int PlayList::rowCount(const QModelIndex &parent = QModelIndex()) const
{
    if (parent.isValid()) return 0;
    switch (mMode) {
    case PLAYLIST:
        return mData.length();
    case ARTISTLIST:
        return mArtist.length();
    case ALBUMLIST:
        return mAlbum.length();
    case MYLIST:
        return mFavourite.length();
    default:
        return 0;
    }
}

QVariant PlayList::data(const QModelIndex &index, int role) const
{
    //    qDebug() << __FUNCTION__;
    if(index.isValid() == false) return QVariant();
    switch (mMode) {
    case PLAYLIST:
        switch (role) {
        case LoveRole:
            return mData.at(index.row())->getLove();
        case ImageRole:
            return mData.at(index.row())->getImage();
        default:
            return mData.at(index.row())->getValue(role);
        }
    case ARTISTLIST:
        if (count() == 0) return QVariant();
        switch (role)
        {
        case ImageRole:
            return mArtist.at(index.row()).at(0).getImage();
        default:
            return mArtist.at(index.row()).at(0).getValue(role);
        }
        //        return mArtist.at(index.row()).getSongContent(0, role);
    case ALBUMLIST:
        if (count() == 0) return QVariant();
        switch (role) {
        case ImageRole:
            return mAlbum.at(index.row()).at(0).getImage();
        default:
            return mAlbum.at(index.row()).at(0).getValue(role);
        }
        //        return mAlbum.at(index.row()).getSongContent(0, role);
    case MYLIST:
        switch (role) {
        case LoveRole:
            return mFavourite.at(index.row())->getLove();
        case ImageRole:
            return mFavourite.at(index.row())->getImage();
        default:
            return mFavourite.at(index.row())->getValue(role);
        }
    default:
        return QVariant();
    }

}

SongElement* PlayList::findSong(QList<SongElement*> list, const QString source)
{
    SongElement* tmp = nullptr;
    for (SongElement* itr : list)
    {
        if (*itr == source) tmp = itr;
    }
    return tmp;
}

void PlayList::addFiletoArt(SongElement* temp)
{
    //    qDebug() << __FUNCTION__ << "begin";
    auto itr = std::find(mArtist.begin(), mArtist.end(), temp->getValue(Roles::ContributingArtistRole));
    if (itr != mArtist.end())
    {
        (*itr).addSong(temp);
    }
    else {
        ArtistElement newArt(temp->getValue(Roles::ContributingArtistRole));
        mArtist.append(newArt);
        mArtist.back().addSong(temp);
    }
    emit layoutChanged();
    //    qDebug() << __FUNCTION__ << "end";
}

void PlayList::addFiletoAlb(SongElement* temp)
{
    //    qDebug() << __FUNCTION__ << "begin";
    auto itr = std::find(mAlbum.begin(), mAlbum.end(), temp->getValue(Roles::AlbumTitleRole));
    if (itr != mAlbum.end())
    {
        itr->addSong(temp);
    }
    else {
        AlbumElement newAlb(temp->getValue(Roles::AlbumTitleRole));
        newAlb.addSong(temp);
        mAlbum.append(newAlb);
    }
    emit layoutChanged();
    //    qDebug() << __FUNCTION__ << "end";
}

void PlayList::addNewFiles(const QList<QUrl> &list)
{
    for (QUrl url: list)
    {
        SongLoader* loaderptr = new SongLoader;
        QObject::connect(loaderptr, &SongLoader::sendNewSong, this, &PlayList::addNewSong);
        loaderptr->loadNewSong(url, false);
    }
}

QStringList PlayList::addFavourite(int index)
{
    qDebug() << __FUNCTION__ << "begin";
    switch (mMode) {
    case PLAYLIST:
    {
        auto itr = std::find(mFavourite.begin(), mFavourite.end(), mData.at(index));
        if (itr == mFavourite.end())
        {
            mData.at(index)->setLove(true);
            mFavourite.append(mData.at(index));
        } else
        {
            (*itr)->setLove(false);
            mFavourite.removeOne(*itr);
        }
    }
        break;
    case MYLIST:
    {
        auto itr = std::find(mFavourite.begin(), mFavourite.end(), mFavourite.at(index));
        SongElement* itr2 = findSong(mData, mFavourite.at(index)->getValue(SourceRole));
//        (*itr)->setLove(false);
        mFavourite.removeOne(*itr);
        if (itr2 != nullptr)
        {
            (itr2)->setLove(false);
        } else
        {
            delete itr2;
        }
    }
        break;
    default:
        break;
    }
    QStringList myLoveList;
    for (SongElement* song : mFavourite)
    {
        myLoveList.append(song->getValue(SourceRole));
    }
    emit layoutChanged();
    return myLoveList;
}

void PlayList::getFavouriteList(QStringList list)
{
    qDebug() << __FUNCTION__ << list;
    for (QString path: list)
    {
        SongLoader* loaderptr = new SongLoader;
        QObject::connect(loaderptr, &SongLoader::sendNewLoveSong, this, &PlayList::addNewLoveSong);
        loaderptr->loadNewSong(QUrl(path), true);
    }
}

const SongElement& PlayList::at(int row) const
{
    //        qDebug() << __FUNCTION__ << "row: " << row << mCurrentArtist << mCurrentAlbum;
    switch (mMode) {
    case PLAYLIST:
        return *mData.at(row);
    case ARTISTLIST:
        return mArtist.at(mCurrentArtist).at(row);
    case ALBUMLIST:
        return mAlbum.at(mCurrentAlbum).at(row);
    case MYLIST:
        return *mFavourite.at(row);
    default:
        return SongElement();
    }
}

void PlayList::clear()
{
    for(SongElement* elm: mData)
    {
        if (std::find(mFavourite.begin(),mFavourite.end(),elm) == mFavourite.end())
            delete elm;
    }
    mData.clear();
    mArtist.clear();
    mAlbum.clear();
    emit layoutChanged();
}

void PlayList::sortList(bool asc)
{
    if (asc)
    {
        std::sort(mData.begin(), mData.end(), [](SongElement* a, SongElement* b){return *a <*b;});
    }
    else
    {
        std::sort(mData.begin(), mData.end(), [](SongElement* a, SongElement* b){return *a >*b;});
    }
    emit layoutChanged();
}

QHash<int, QByteArray> PlayList::roleNames() const
{
    return mRoleNames;
}

void PlayList::addNewSong(const QStringList newSong, const QImage newImage, SongLoader* ptr)
{
    delete ptr;
    if (findSong(mData, newSong[0]) == nullptr)
    {
        beginInsertRows(QModelIndex(), count(), count());
        SongElement* itr = findSong(mFavourite, newSong[0]);
        if (itr != nullptr) mData.append(itr);
        else mData.append(new SongElement(newSong, newImage));
        addFiletoAlb(mData.last());
        addFiletoArt(mData.last());
        endInsertRows();
    }
    emit layoutChanged();
}

void PlayList::addNewLoveSong(const QStringList newSong, const QImage newImage, SongLoader *ptr)
{
    delete ptr;
    beginInsertRows(QModelIndex(), count(), count());
    SongElement* itr = findSong(mData, newSong[0]);
    if (itr != nullptr)  mFavourite.append(itr);
    else mFavourite.append(new SongElement(newSong, newImage));
    mFavourite.last()->setLove(true);
    endInsertRows();
    emit layoutChanged();
}


int PlayList::currentArtist() const
{
    return mCurrentArtist;
}

bool PlayList::setCurrentArtist(int newCurrentArtist)
{
    if (newCurrentArtist >= mArtist.count())
        return false;
    if (mCurrentArtist == newCurrentArtist)
        return true;
    mCurrentArtist = newCurrentArtist;
    qDebug() << __FUNCTION__ << mCurrentArtist;
    emit currentArtistChanged();
    return true;
}

int PlayList::currentAlbum() const
{
    return mCurrentAlbum;
}

bool PlayList::setCurrentAlbum(int newCurrentAlbum)
{
    if (newCurrentAlbum >= mAlbum.count()) return false;
    if (mCurrentAlbum == newCurrentAlbum) return true;
    mCurrentAlbum = newCurrentAlbum;
    emit currentAlbumChanged();
    qDebug() << __FUNCTION__ << mCurrentAlbum;
    return true;
}

MODE PlayList::currentMode() const
{
    return mMode;
}

void PlayList::setCurrentMode(MODE newCurrentMode)
{
    if (mMode == newCurrentMode)
        return;
    mMode = newCurrentMode;
    mCurrentAlbum = 0;
    mCurrentArtist = 0;
    emit currentModeChanged();
    emit layoutChanged();
    //    qDebug() << __FUNCTION__ << mMode;
}
