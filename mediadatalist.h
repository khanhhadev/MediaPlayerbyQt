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

struct MediaDataItem {
    MediaDataItem(QString fileSource) : source(fileSource)
    {
        QMediaPlayer* mTemp = new QMediaPlayer;
        mTemp->setSource(source);
        QMediaMetaData songContext = mTemp->metaData();
        name = songContext.stringValue(QMediaMetaData::Title);
        album = songContext.stringValue(QMediaMetaData::AlbumTitle);
        artist = songContext.stringValue(QMediaMetaData::ContributingArtist);
        date = songContext.value(QMediaMetaData::Date).toDate().toString("dd/MM/yyyy");
    }
    QString source, name, album, artist, date;
};


enum Roles {
    ModelDataRole = Qt::UserRole+1,
    SourceRole,
    NameRole,
    AlbumTitleRole,
    ContributingArtistRole,
    DateRole
};

class MediaDataList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MediaDataList(QObject *parent = nullptr);
    MediaDataList(const MediaDataList& data);
    virtual ~MediaDataList();

    int count() const;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    void addNewFolder(const QUrl directorypath);

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
