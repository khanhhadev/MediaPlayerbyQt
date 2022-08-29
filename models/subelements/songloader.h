/***********************************************
*USED TO LOAD LIST OF SONG CONTENT
************************************************/
#ifndef SONGLOADER_H
#define SONGLOADER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QImage>

class SongLoader : public QObject
{
    Q_OBJECT
public:
    explicit SongLoader(QObject *parent = nullptr);

    void loadNewSong(QUrl, bool);

signals:
    void sendNewSong(QStringList newSong, QImage newImage, SongLoader* );
    void sendNewLoveSong(QStringList newSong, QImage newImage, SongLoader* );

public slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
private:
    QMediaPlayer* mLoader;
    QAudioOutput* mAu;
    QList<QUrl> mList;
    bool mLoveSong;
};

#endif // SONGLOADER_H
