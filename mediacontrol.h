#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include "mediadatalist.h"
#include "player.h"
#include "browserdialog.h"
#include <QObject>

class MediaControl : public QObject
{
    Q_PROPERTY(MediaDataList songList READ getSongList WRITE setSongList NOTIFY songListChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_OBJECT
public:
    explicit MediaControl(QObject *parent = nullptr);

    //mDirectory READ-WRITE function
    void setDirectory(const QString dir);
    QString getDirectory() const;

    //mSongList READ-WRITE function
    void setSongList(MediaDataList newSongList);
    MediaDataList getSongList() const;

    //mcurrentIndex READ-WRITE function
    int getCurrentIndex() const;
    void setCurrentIndex(const int currentIndex);

    void nextSong();
    void previousSong();
signals:
    void currentIndexChanged();
    void directoryChanged();

public slots:
    void onChangingDirectory(QString path);
    void onEndOfList();
    void onSourceChanged(QString);
    void onCurrentIndexChanged();

private:
    //PROPERTY
    Player myPlayer;
    MediaDataList myData;
    BrowserDialog myBrowser;
    int mCurrentIndex;
    QString mDirectory;
    const QString mDataFileLocation = (QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/MusicPlayer");

    //FUNCTION
    void readBackup();
    void writeBackup();
};

#endif // MEDIACONTROL_H
