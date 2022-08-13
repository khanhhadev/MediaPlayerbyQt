/***********************************************
*THIS CLASS IS USED MANAGE PLAY LIST
************************************************/

#ifndef MEDIADATALIST_H
#define MEDIADATALIST_H

#include <QObject>
#include <QFileSystemModel>
#include <QUrl>
#include <QAbstractListModel>
#include <QStandardPaths>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QDateTime>


enum Roles {
    SourceRole = Qt::UserRole+1,
    NameRole,
    AlbumTitleRole,
    ContributingArtistRole,
    DateRole
};

struct MediaDataItem {
    MediaDataItem(QString fileSource, QString fileName) : source(fileSource), name(fileName)
    {
//        QMediaPlayer mTemp;
//        mTemp.setSource(source);
//        if (mTemp.isAvailable())
//        {
//            QMediaMetaData songContext = mTemp.metaData();
//            //name = songContext.stringValue(QMediaMetaData::Title);
//            album = songContext.stringValue(QMediaMetaData::AlbumTitle);
//            artist = songContext.stringValue(QMediaMetaData::ContributingArtist);
//            date = songContext.value(QMediaMetaData::Date).toDate().toString("dd/MM/yyyy");
//            qDebug() << __FUNCTION__ << source << name << album << artist << date;
//        }
//        qDebug() << __FUNCTION__ << source << name << album << artist << date;
    }

    QString getValue(int role) const
    {
        switch (role)
        {
        case Roles::SourceRole:
            return source;
            break;
        case Roles::NameRole:
            return name;
            break;
        case Roles::AlbumTitleRole:
            return album;
            break;
        case Roles::ContributingArtistRole:
            return artist;
            break;
        case Roles::DateRole:
            return date;
            break;
        default:
            return "";
        }
    }
    bool operator==(const MediaDataItem& item)
    {
        return (source == item.source)&&(name == item.name)
                && (album == item.album) && (artist == item.artist)
                && (date == item.date);
    }
private:
    QString source, name, album, artist, date;
};

class MediaDataList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MediaDataList(QObject *parent = nullptr);

    int count() const;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void addNewFiles(const MediaDataItem &file);
    void addNewFiles(const QList<MediaDataItem> &list);
    MediaDataItem at(int row);
    void clear();



    //    friend QDebug& operator<<(QDebug& output, const MediaDataList& list);
protected:
    QHash<int, QByteArray> roleNames() const override ;

signals:
    void songListChanged();

public slots:

private:
    //    QString m_RootFolder;
    QList<MediaDataItem> mData;
    QHash<int, QByteArray> mRoleNames;
};

#endif // MEDIADATALIST_H

//    Q_PROPERTY(QStringList songList READ getSongList WRITE setSongList NOTIFY songListChanged)
//    Q_PROPERTY(QString directory READ getDirectory WRITE setDirectory NOTIFY directoryChanged)
//    Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
//public:
//    explicit MediaData(QObject *parent = nullptr);

//    //get list of song from directory path
//    void getURLList(QUrl dir);

//    //mDirectory READ-WRITE function
//    void setDirectory(const QString dir);
//    QString getDirectory() const;

//    //mSongList READ-WRITE function
//    void setSongList(const QStringList newSongList);
//    QStringList getSongList() const;

//    //mcurrentIndex READ-WRITE function
//    int getCurrentIndex() const;
//    void setCurrentIndex(const int currenIndex);

//signals:
//    void directoryChanged();
//    void songListChanged();
//    void sourceChanged(QString path);
//    void endOfList();
//    void currentIndexChanged(int currentindex);

//public slots:
//    void onDirectoryChanged();
//    void onSongListChanged();
//    void onCurrentIndexChanged();

//private:
//    QStringList mSongList;
//    //get-set mDirectory backup to AppData.txt file
//    void readBackup();
//    void writeBackup();
