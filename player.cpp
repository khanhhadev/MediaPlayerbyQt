#include "player.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QImage>
#include <QMediaMetaData>

Player::Player(QObject *parent)
    : QObject{parent}
{
    connect(&(this->mMPlayer), SIGNAL(positionChanged(qint64)),
            this, SIGNAL(positionChanged(qint64)));

    connect(&(this->mMPlayer), SIGNAL(durationChanged(qint64)),
            this, SIGNAL(durationChanged(qint64)));

    connect(&(this->mMPlayer), SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this, SLOT(isPlaying()));

    connect(&(this->mMPlayer), SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(onMediaStatusChanged()));

    mAudio = new QAudioOutput;
    mAudio->setVolume(0.5);
    mMPlayer.setAudioOutput(mAudio);
}

void Player::play()
{
    if (!mMPlayer.source().isEmpty())
    {
        mMPlayer.play();
        emit stateChanged();
        qDebug() << __FUNCTION__ << mMPlayer.source();
    }
}

void Player::pause()
{
    if (mMPlayer.playbackState() == QMediaPlayer::PlayingState)
    {
        mMPlayer.pause();
        emit stateChanged();
        qDebug() << __FUNCTION__<< mMPlayer.source();
    }
}

void Player::stop()
{
    mMPlayer.stop();
    emit stateChanged();
    qDebug() << __FUNCTION__<< mMPlayer.source();
}

void Player::mute()
{
    setVolume(0);
}

void Player::unmute()
{
    setVolume(0.5);
}

QString Player::getDurationText()
{
    long long int dura = getDuration();
    long long int ms = dura % 1000;
    long long int s = (dura /= 1000)%60;
    long long int m = (dura /= 60)/60;
    long long int h = dura;
//    qDebug() << __FUNCTION__ << getDuration() << QTime(h, m, s, ms).toString("hh:mm:ss");
    return QTime(h, m, s, ms).toString("hh:mm:ss");
}

QString Player::getPositionText()
{
    long long int posi = getPosition();
    long long int ms = posi % 1000;
    long long int s = (posi /= 1000)%60;
    long long int m = (posi /= 60)/60;
    long long int h = posi;
//    qDebug() << __FUNCTION__ << getPosition() << QTime(h, m, s, ms).toString("hh:mm:ss");
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

void Player::getSongCover()
{
    QMediaMetaData songData = mMPlayer.metaData();
    QImage mImage(songData[QMediaMetaData::CoverArtImage].value<QImage>());


    //    painter->drawImage(0,0, mImage);
    //    painter->setOpacity(1);
}

qint64 Player::getPosition() const
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
        qDebug() << __FUNCTION__<< mMPlayer.source();
    }
}

qreal Player::getVolume() const
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

qint64 Player::getDuration() const
{
    return mMPlayer.duration();
}

void Player::onSourceChanged(QString songpath)
{
    mMPlayer.setSource(songpath);
    qDebug() << __FUNCTION__ << songpath;
}

void Player::onMediaStatusChanged()
{
    if (mMPlayer.mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        emit endOfSong();
        play();
    }
}

