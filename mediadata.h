/***********************************************
*THIS CLASS IS USED MANAGE PLAY LIST
************************************************/

#ifndef MEDIADATA_H
#define MEDIADATA_H

#include <QObject>
#include <QFileSystemModel>
#include <QUrl>
#include <QStandardPaths>

class MediaData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList songList READ getSongList WRITE setSongList NOTIFY songListChanged)
    Q_PROPERTY(QString directory READ getDirectory WRITE setDirectory NOTIFY directoryChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
public:
    explicit MediaData(QObject *parent = nullptr);

    //get list of song from directory path
    void getURLList(QUrl dir);

    //mDirectory READ-WRITE function
    void setDirectory(const QString dir);
    QString getDirectory() const;

    //mSongList READ-WRITE function
    void setSongList(const QStringList newSongList);
    QStringList getSongList() const;

    //mcurrentIndex READ-WRITE function
    int getCurrentIndex() const;
    void setCurrentIndex(const int currenIndex);

signals:
    void directoryChanged();
    void songListChanged();
    void sourceChanged(QString path);
    void endOfList();
    void currentIndexChanged(int currentindex);

public slots:
    void onDirectoryChanged();
    void onSongListChanged();
    void onCurrentIndexChanged();
    void onChangingDirectory(QString path);
    void nextSong();

private:
    QStringList mSongList;
    QString mDirectory;
    int mCurrentIndex;
    const QString mDataFileLocation = (QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/MusicPlayer");

    //get-set mDirectory backup to AppData.txt file
    void readBackup();
    void writeBackup();
};

#endif // MEDIADATA_H
