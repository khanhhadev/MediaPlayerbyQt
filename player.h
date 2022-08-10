/***********************************************
*THIS CLASS IS USED MANAGE MEDIA PLAYER & AUDIO OBJECT
************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList songInfor READ getSongInfor WRITE setSongInfor NOTIFY songInforChanged)

public:
    explicit Player(QObject *parent = nullptr);

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
    void positionChanged(qint64);
    void durationChanged(qint64);
    void endOfSong();
    void stateChanged();
    void volumeChanged();
    void mutedChanged();
    void songInforChanged();

public slots:
    void onMediaStatusChanged();

private:
    QMediaPlayer mMPlayer;
    QAudioOutput *mAudio;
};

#endif // PLAYER_H
