#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include "mediadatalist.h"
#include "browserdialog.h"
#include <QObject>

class MediaControl : public QObject
{
    Q_PROPERTY(QMediaPlayer::PlaybackState state READ getState NOTIFY stateChanged)
    Q_PROPERTY(MediaDataList songListModel READ getSongListModel NOTIFY directoryChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(qreal volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(qint64 position READ getPosition WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ getDuration NOTIFY durationChanged)
    Q_PROPERTY(QString positionText READ getPositionText NOTIFY positionChanged)
    Q_PROPERTY(QString durationText READ getDurationText NOTIFY durationChanged)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
    Q_OBJECT
public:
    explicit MediaControl(QObject *parent = nullptr);

    //mDirectory READ-WRITE function
    void setDirectory(const QString dir);
    QString getDirectory() const;

    //mSongList READ-WRITE function
    void setSongListModel(MediaDataList newSongList);
    MediaDataList getSongListModel() const;

    //mcurrentIndex READ-WRITE function
    int getCurrentIndex() const;
    void setCurrentIndex(const int currentIndex);

    Q_INVOKABLE void nextSong();
    Q_INVOKABLE void previousSong();
    Q_INVOKABLE void playpause();

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    Q_INVOKABLE void mute();
    Q_INVOKABLE void unmute();

    Q_INVOKABLE bool isPlaying();
    Q_INVOKABLE bool isPaused();
    Q_INVOKABLE bool isStopped();

    QString getDurationText();
    QString getPositionText();

    qint64 getDuration() const;

    qint64 getPosition() const;
    void setPosition(const qint64);

    QMediaPlayer::PlaybackState getState();
    void setState(const QMediaPlayer::PlaybackState);

    qreal getVolume() const;
    void setVolume(const qreal volume);

    bool muted() const;
    void setMuted(const bool muted);

    void setSource(QString source);

signals:
    void directoryChanged();
    void currentIndexChanged();
    void positionChanged(qint64);
    void durationChanged(qint64);
    void endOfSong();
    void stateChanged();
    void volumeChanged();
    void mutedChanged();
    void songInforChanged();

public slots:
    void onChangingDirectory(QString path);
    void onEndOfList();
    void onEndOfSong();
    void onSourceChanged(QString);
    void onCurrentIndexChanged();
    void onMediaStatusChanged();

private:
    //PROPERTY
    QMediaPlayer myPlayer;
    QAudioOutput *mAudio;
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
