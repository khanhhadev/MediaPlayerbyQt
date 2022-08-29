/***********************************************
*THIS CLASS IS USED MANAGE PLAY LIST
************************************************/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QStandardPaths>
#include <QDateTime>
#include "models/subelements/songelement.h"
#include "models/subelements/albumelement.h"
#include "models/subelements/artistelement.h"
#include "models/subelements/songloader.h"

enum MODE{
    PLAYLIST,
    ARTISTLIST,
    ALBUMLIST,
    MYLIST
};

class PlayList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int currentArtist READ currentArtist WRITE setCurrentArtist NOTIFY currentArtistChanged)
    Q_PROPERTY(int currentAlbum READ currentAlbum WRITE setCurrentAlbum NOTIFY currentAlbumChanged)
    Q_PROPERTY(MODE currentMode READ currentMode WRITE setCurrentMode NOTIFY currentModeChanged)
public:
    explicit PlayList(QObject *parent = nullptr);

    int count() const;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    SongElement* findSong( QList<SongElement*> list, const QString source);

    //add reference pointer to songelement
    void addFiletoArt(SongElement* temp);
    void addFiletoAlb(SongElement* temp);

    //load new list from directory path
    void addNewFiles(const QList<QUrl> &list);

    //add new song to Mylist/remove song from Mylist
    QStringList addFavourite(int index);
    void getFavouriteList(QStringList list);
    void sortList(bool asc);

    const SongElement& at(int row) const;
    void clear();

    int currentArtist() const;
    bool setCurrentArtist(int newCurrentArtist);

    int currentAlbum() const;
    bool setCurrentAlbum(int newCurrentAlbum);

    MODE currentMode() const;
    void setCurrentMode(MODE newCurrentMode);

protected:
    QHash<int, QByteArray> roleNames() const override ;

signals:
    void songListChanged();
    void sourceChanged(QString);
    void currentArtistChanged();
    void currentAlbumChanged();
    void currentModeChanged();

public slots:
    void addNewSong(const QStringList newSong, const QImage newImage, SongLoader* ptr);
    void addNewLoveSong(const QStringList newSong, const QImage newImage, SongLoader* ptr);

private:
    QList<SongElement*> mData;
    QList<ArtistElement> mArtist;
    QList<AlbumElement> mAlbum;
    QList<SongElement*> mFavourite;

    int mCurrentArtist;
    int mCurrentAlbum;

    MODE mMode = MODE::PLAYLIST;
    QHash<int, QByteArray> mRoleNames;
};

#endif // PLAYLIST_H
