#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QFileDialog>
#include <QTime>

#include "models/player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{
    qDebug() << __FUNCTION__;
    connect(&(this->mMPlayer), SIGNAL(positionChanged(qint64)),
            this, SIGNAL(positionChanged(qint64)));

    connect(&(this->mMPlayer), SIGNAL(durationChanged(qint64)),
            this, SIGNAL(durationChanged(qint64)));

    connect(&(this->mMPlayer), SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this, SLOT(isPlaying()));

    connect(&(this->mMPlayer), SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(onMediaStatusChanged()));

    setImage(QImage((":/image/main.jpg")));
    mAudio = new QAudioOutput;
    mAudio->setVolume(0.5);
    mMPlayer.setAudioOutput(mAudio);
}

//set media player to play mode
void Player::play()
{
    if (!mMPlayer.source().isEmpty())
    {
        mMPlayer.play();
        emit stateChanged();
    }
}

//set media player to pause mode
void Player::pause()
{
    if (mMPlayer.playbackState() == QMediaPlayer::PlayingState)
    {
        mMPlayer.pause();
        emit stateChanged();
    }
}

//set media player to stop mode
void Player::stop()
{
    mMPlayer.stop();
    emit stateChanged();
}

//set mute to audio
void Player::mute()
{
    setMuted(true);
}

//set unmute to audio
void Player::unmute()
{
    setMuted(false);
}

//return song duration by text
QString Player::durationText()
{
    long long int dura = duration();
    /*long long */int ms = dura % 1000;
    /*long long */int s = (dura /= 1000)%60;
    /*long long */int m = (dura /= 60)%60;
    /*long long */int h = dura / 60;
    return QTime(h, m, s, ms).toString("hh:mm:ss");
}

//return song position by text
QString Player::positionText()
{
    long long int posi = position();
    /*long long */int ms = posi % 1000;
    /*long long */int s = (posi /= 1000)%60;
    /*long long */int m = (posi /= 60)%60;
    /*long long */int h = posi / 60;
    return QTime(h, m, s, ms).toString("hh:mm:ss");
}

bool Player::isPlaying()
{
    return (mMPlayer.playbackState() == QMediaPlayer::PlayingState);
}

bool Player::isPaused()
{
    return (mMPlayer.playbackState() == QMediaPlayer::PausedState);
}

bool Player::isStopped()
{
    return (mMPlayer.playbackState() == QMediaPlayer::StoppedState);
}

qint64 Player::position() const
{
    return mMPlayer.position();
}

void Player::setPosition(const qint64 position)
{
    if (position != mMPlayer.position())
    {

        if (position > mMPlayer.duration()) mMPlayer.setPosition(mMPlayer.duration());
        else
        {
            if (position < 0) mMPlayer.setPosition(0);
            else mMPlayer.setPosition(position);
        }
    }
}

QMediaPlayer::PlaybackState Player::getState()
{
    return mMPlayer.playbackState();
}

void Player::setState(const QMediaPlayer::PlaybackState state)
{
    if (state != mMPlayer.playbackState())
    {
        switch(state)
        {
        case 0:
            mMPlayer.stop();
            break;
        case 1:
            mMPlayer.play();
            break;
        case 2:
            mMPlayer.stop();
            break;
        default:
            break;
        }
        emit stateChanged();
    }
}

qreal Player::volume() const
{
    return mAudio->volume();
}

void Player::setVolume(const qreal volume)
{
    if (volume != mAudio->volume())
    {
        if (volume > 1) mAudio->setVolume(1);
        else
        {
            if (volume < 0) mAudio->setVolume(0);
            else mAudio->setVolume(volume);
        }
        emit volumeChanged();
    }
}

bool Player::muted() const
{
    return mAudio->isMuted();
}

void Player::setMuted(const bool muted)
{
    mAudio->setMuted(muted);
    emit mutedChanged();
}

bool Player::repeat() const
{
    return (mMPlayer.loops() < 0);
}

void Player::setRepeat(const bool repeat)
{
    if (repeat) {
        mMPlayer.setLoops(QMediaPlayer::Infinite);
    } else {
        mMPlayer.setLoops(QMediaPlayer::Once);
    }
    emit repeatChanged();
    qDebug() << mMPlayer.loops();
}

void Player::setSource(QString source)
{
//    static int count = 0; qDebug() << __FUNCTION__ << ++count;
    mMPlayer.setSource(source);
    if (source == "") setImage(QImage(":/image/main.jpg"));
}

qint64 Player::duration() const
{
    return mMPlayer.duration();
}

void Player::onMediaStatusChanged()
{
    switch(mMPlayer.mediaStatus())
    {
    case QMediaPlayer::EndOfMedia:
    {
        emit endOfSong();
    }
        break;
    case QMediaPlayer::LoadedMedia:
    {
        QMediaMetaData songcontent = mMPlayer.metaData();
        setImage(songcontent[QMediaMetaData::ThumbnailImage].value<QImage>());
        emit imageChanged();
    }
        break;
    default:
        break;
    }
}

void Player::onErrorChanged(QMediaPlayer::Error error)
{

}

void Player::onSourceChanged(QString source)
{
    setSource(source);
}

const QImage &Player::image() const
{
    return mImage;
}

void Player::setImage(const QImage newimage)
{
    mImage = newimage;
//    mImage.scaled(1000, 1000, Qt::KeepAspectRatio);
    emit imageChanged();
}
