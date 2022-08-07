#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 position READ getPosition WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ getDuration NOTIFY durationChanged)
    Q_PROPERTY(QMediaPlayer::PlaybackState state READ getState WRITE setState NOTIFY stateChanged)

public:
    explicit Player(QObject *parent = nullptr);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    qint64 getDuration() const;

    qint64 getPosition() const;
    void setPosition(const qint64);

    QMediaPlayer::PlaybackState getState();
    void setState(const QMediaPlayer::PlaybackState);

    Q_INVOKABLE bool isPlaying();
    Q_INVOKABLE bool isPaused();
    Q_INVOKABLE bool isStopped();
signals:
//    void CurrentSongChanged(qint64 currentIndex);
    void positionChanged(qint64);
    void durationChanged(qint64);
    void stateChanged();
public slots:
    void onSourceChanged(QString);

private:
    QMediaPlayer mMPlayer;
    QAudioOutput *mAudio;
};

#endif // PLAYER_H
