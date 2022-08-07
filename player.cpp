#include "player.h"
#include <QMediaPlayer>
#include <QAudioOutput>

Player::Player(QObject *parent)
    : QObject{parent}
{
    connect(&(this->mMPlayer), SIGNAL(positionChanged(qint64)),
            this, SIGNAL(positionChanged(qint64)));
    connect(&(this->mMPlayer), SIGNAL(durationChanged(qint64)),
            this, SIGNAL(durationChanged(qint64)));

    connect(&(this->mMPlayer), SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this, SLOT(isPlaying()));

    mAudio = new QAudioOutput;
    mAudio->setVolume(0.8);
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

qint64 Player::getPosition() const
{
    return mMPlayer.position();
}
void Player::setPosition(const qint64 position)
{
    if (position != mMPlayer.position())
    {
        mMPlayer.setPosition(position);
        emit positionChanged(mMPlayer.position());
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

qint64 Player::getDuration() const
{
    return mMPlayer.duration();
}

void Player::onSourceChanged(QString songpath)
{
    mMPlayer.setSource(songpath);
    qDebug() << __FUNCTION__ << songpath;
}

