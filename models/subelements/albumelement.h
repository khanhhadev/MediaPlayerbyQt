/***********************************************
*USED TO STORE LIST OF SONG WITH SAME ALBUM
************************************************/

#ifndef ALBUMELEMENT_H
#define ALBUMELEMENT_H

#include <QList>
#include <QVariant>
#include "models/subelements/songelement.h"

class AlbumElement
{
public:
//    AlbumElement();
    AlbumElement(QString name);
    void addSong(SongElement* newSong);
    const SongElement& at(int row) const;
    QString getName() const;
    QVariant getSongContent(int row, int role) const;
    int count() const;

    bool operator==(const AlbumElement& album);
    bool operator==(const QString& albumname);
private:
    QString mName;
    QList<SongElement*> mData;
};

#endif // ALBUMELEMENT_H
