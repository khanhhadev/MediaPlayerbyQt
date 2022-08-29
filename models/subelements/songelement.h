/***********************************************
*USED TO STORE SONG CONTENT
************************************************/
#ifndef SONGELEMENT_H
#define SONGELEMENT_H

#include <QObject>
#include <QUrl>
#include <QVariant>
#include <QDebug>
#include <QImage>

enum Roles {
    SourceRole = Qt::UserRole+1,
    NameRole,
    AlbumTitleRole,
    ContributingArtistRole,
    ImageRole,
    LoveRole
};

class SongElement
{
public:
    SongElement();
    SongElement(QStringList newSong, QImage newImage);
    ~SongElement();

    QString getValue(int role) const;
    QImage getImage() const;

    bool getLove() const;
    void setLove(const bool newlLove);

    bool operator==(const SongElement& item);
    bool operator==(SongElement& item);
    bool operator==(const QString& item);

    bool operator>(const SongElement& item);

    bool operator<(const SongElement& item);

    friend QDebug& operator<<(QDebug& output, SongElement item);

private:
    QString source, name, album, artist, date;
    QImage image;
    bool love = false;
};

#endif // SONGELEMENT_H
