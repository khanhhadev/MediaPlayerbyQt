#include "artistelement.h"


//ArtistElement::ArtistElement()
//{
//    qDebug() << __FUNCTION__;
//}

ArtistElement::ArtistElement(QString Name): mName(Name)
{
    //    qDebug() << __FUNCTION__;
};

void ArtistElement::addSong(SongElement* newSong)
{
    mData.append(newSong);
//    qDebug() << __FUNCTION__ << mData.back();
}

const SongElement& ArtistElement::at(int row) const
{
//    qDebug() << __FUNCTION__ << this->getName();
    //    qDebug() << __FUNCTION__ << mData.at(row)->getValue(Roles::SourceRole);
    return *(mData.at(row));
}

QString ArtistElement::getName() const
{
    return mName;
}

QVariant ArtistElement::getSongContent(int row, int role) const
{
    switch (role)
    {
    case Roles::ImageRole:
        return mData.at(row)->getImage();
    default:
        return mData.at(row)->getValue(role);
    }
}

int ArtistElement::count() const
{
    return mData.count();
}

bool ArtistElement::operator==(const ArtistElement &artist)
{
    return (mName == artist.mName);
}

bool ArtistElement::operator==(const QString& artistname)
{
    return (mName == artistname);
}
