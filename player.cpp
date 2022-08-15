#include "player.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QTime>

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
    mCurrentSong.append(QList<QString>{"", "", "", "", ""});
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
QString Player::getDurationText()
{
    long long int dura = getDuration();
    long long int ms = dura % 1000;
    long long int s = (dura /= 1000)%60;
    long long int m = (dura /= 60)/60;
    long long int h = dura;
    return QTime(h, m, s, ms).toString("hh:mm:ss");
}

//return song position by text
QString Player::getPositionText()
{
    long long int posi = getPosition();
    long long int ms = posi % 1000;
    long long int s = (posi /= 1000)%60;
    long long int m = (posi /= 60)/60;
    long long int h = posi;
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
    mMPlayer.setSource(source);
    clearSongInfor();
}

QStringList Player::getCurrentSong() const
{
    return mCurrentSong;
}

void Player::clearSongInfor()
{
    for (int i = 0; i< 5; i ++)
        mCurrentSong[i] = "";
    emit currentSongChanged();
}


qint64 Player::getDuration() const
{
    return mMPlayer.duration();
}

void Player::onMediaStatusChanged()
{
    if (mMPlayer.mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        emit endOfSong();
    }
    if (mMPlayer.mediaStatus() == QMediaPlayer::LoadedMedia)
    {
        QMediaMetaData songcontent = mMPlayer.metaData();

        mCurrentSong[0] = mMPlayer.source().toString();
        mCurrentSong[1] = songcontent.stringValue(QMediaMetaData::Title);
        mCurrentSong[2] = songcontent.stringValue(QMediaMetaData::AlbumTitle);
        mCurrentSong[3] = songcontent.stringValue(QMediaMetaData::ContributingArtist);
        mCurrentSong[4] = songcontent.value(QMediaMetaData::Date).toDate().toString("dd/MM/yyyy");
        emit currentSongChanged();
    }
}

void Player::onSourceChanged(QString source)
{
    setSource(source);
}

