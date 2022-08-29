#include "songloader.h"

SongLoader::SongLoader(QObject *parent)
    : QObject{parent}
{
    mLoader = new QMediaPlayer;
    mAu = new QAudioOutput;
    connect(this->mLoader, &QMediaPlayer::mediaStatusChanged,
            this, &SongLoader::onMediaStatusChanged);
    mAu->setVolume(0.1);
    mLoader->setAudioOutput(mAu);
}

void SongLoader::loadNewSong(QUrl url, bool lovesong)
{
    mLoveSong = lovesong;
    mLoader->setSource(url);
}

void SongLoader::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch(status)
    {
    case QMediaPlayer::LoadedMedia:
    {
        QStringList mCurrentSong;
        QImage mCurrentImage;

        QMediaMetaData songcontent = mLoader->metaData();

        mCurrentSong << mLoader->source().toString()
                     << songcontent.stringValue(QMediaMetaData::Title)
                     << songcontent.stringValue(QMediaMetaData::AlbumTitle)
                     << songcontent.stringValue(QMediaMetaData::ContributingArtist);
        mCurrentImage = songcontent[QMediaMetaData::ThumbnailImage].value<QImage>();

        //        qDebug() << __FUNCTION__ << mLoader->source().toString();
        if (mLoveSong)
            emit sendNewLoveSong(mCurrentSong, mCurrentImage, this);
        else
            emit sendNewSong(mCurrentSong, mCurrentImage, this);
        //        loadNewSong();
    }
        break;

    default:
        break;
    }
}
