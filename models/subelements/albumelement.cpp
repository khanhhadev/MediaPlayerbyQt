#include "albumelement.h"

//AlbumElement::AlbumElement()
//{
//    qDebug() << __FUNCTION__;
//}

AlbumElement::AlbumElement(QString name): mName(name)
{
    //    qDebug() << __FUNCTION__;
};

void AlbumElement::addSong(SongElement* newSong)
{
    mData.append(newSong);
}

const SongElement& AlbumElement::at(int row) const
{
//    qDebug() << __FUNCTION__ << row;
    return *mData.at(row);
}

QString AlbumElement::getName() const
{
    return mName;
}

QVariant AlbumElement::getSongContent(int row, int role) const
{
    switch (role)
    {
    case Roles::ImageRole:
        return mData.at(row)->getImage();
    default:
        return mData.at(row)->getValue(role);
    }
}

int AlbumElement::count() const
{
    return mData.count();
}

bool AlbumElement::operator==(const AlbumElement &album)
{
    return (mName == album.mName);
}

bool AlbumElement::operator==(const QString& albumname)
{
    return (mName == albumname);
};
