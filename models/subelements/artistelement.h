/***********************************************
*USED TO STORE LIST OF SONG WITH SAME ARTIST
************************************************/
#ifndef ARTISTELEMENT_H
#define ARTISTELEMENT_H

#include <QList>
#include <QVariant>
#include "models/subelements/songelement.h"
class ArtistElement
{
public:
//    ArtistElement();
    ArtistElement(QString Name);
    void addSong(SongElement* newSong);
    const SongElement& at(int row) const;
    QString getName() const;
    QVariant getSongContent(int row, int role) const;
    int count() const;

    bool operator==(const ArtistElement& artist);
    bool operator==(const QString& artistname);
private:
    QString mName;
    QList<SongElement*> mData;
};

#endif // ARTISTELEMENT_H
