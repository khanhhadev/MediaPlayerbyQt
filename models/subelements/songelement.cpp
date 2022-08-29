#include "songelement.h"

//SongElement::SongElement(QUrl fileSource)
//{
//    source = fileSource.toString();
//    name = fileSource.fileName();
//}

SongElement::SongElement()
{
//    qDebug() << __FUNCTION__;
}

SongElement::SongElement(QStringList newSong, QImage newImage)
{
    source = newSong[0];
    name = newSong[1];
    album = newSong[2];
    artist = newSong[3];
    image = newImage;
    //    qDebug() << __FUNCTION__ << this << newSong[1];
}

SongElement::~SongElement()
{
    qDebug() << __FUNCTION__ << this;
}

QString SongElement::getValue(int role) const
{
    switch (role)
    {
    case SourceRole:
        return source;
    case NameRole:
        return name;
    case AlbumTitleRole:
        return album;
    case ContributingArtistRole:
        return artist;
    default:
        return "";
    }
}

QImage SongElement::getImage() const
{
    return image;
}

bool SongElement::getLove() const
{
    return love;
}

void SongElement::setLove(const bool newlLove)
{
    love = newlLove;
}

bool SongElement::operator==(const SongElement& item)
{
//    qDebug() << __FUNCTION__;
    return (source == item.source);
}

bool SongElement::operator==(SongElement& item)
{
//    qDebug() << __FUNCTION__;
    return (source == item.source);
}

bool SongElement::operator==(const QString& itemsource)
{
//    qDebug() << __FUNCTION__;
    return (source == itemsource);
}

bool SongElement::operator>(const SongElement& item)
{
//    qDebug() << __FUNCTION__ << name << item.name;
    return QString::compare(name, item.name) > 0;
}

bool SongElement::operator<(const SongElement& item)
{
//    qDebug() << __FUNCTION__ << name << item.name;
    return QString::compare(name, item.name) < 0;
}

QDebug& operator<<(QDebug& output, SongElement item)
{
    output << item.source << item.name << item.album << item.artist;
    return output;
}
