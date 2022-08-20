/***********************************************
*THIS CLASS IS USED MANAGE PLAY LIST
************************************************/

#ifndef MEDIADATALIST_H
#define MEDIADATALIST_H

#include <QObject>
#include <QUrl>
#include <QDir>
#include <QAbstractListModel>
#include <QStandardPaths>
#include <QDateTime>


enum Roles {
    SourceRole = Qt::UserRole+1,
    NameRole,
    AlbumTitleRole,
    ContributingArtistRole,
    DateRole
};

class MediaDataItem
{
public:
    MediaDataItem(QUrl fileSource)
    {
        source = fileSource.toString();
        name = fileSource.fileName();
    }

    QString getValue(int role) const
    {
        switch (role)
        {
        case Roles::SourceRole:
            return source;
            break;
        case Roles::NameRole:
            return name;
            break;
        case Roles::AlbumTitleRole:
            return album;
            break;
        case Roles::ContributingArtistRole:
            return artist;
            break;
        case Roles::DateRole:
            return date;
            break;
        default:
            return "";
        }
    }

    bool operator==(const MediaDataItem& item)
    {
        return (source == item.source)&&(name == item.name)
                && (album == item.album) && (artist == item.artist)
                && (date == item.date);
    }
    bool operator>(const MediaDataItem& item)
    {
        return QString::compare(name, item.name) > 0;
    }
    bool operator<(const MediaDataItem& item)
    {
        return QString::compare(name, item.name) < 0;
    }

    friend QDebug& operator<<(QDebug& output, const MediaDataItem& item)
    {
        output << item.source << item.name << item.album << item.artist;
        return output;
    }
//public slots:
//    void onSongContentLoaded()
//    {

//    }
private:
    QString source, name, album, artist, date;
};


class MediaDataList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MediaDataList(QObject *parent = nullptr);

    int count() const;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void addNewFiles(const QUrl &file);
    void addNewFiles(const QList<QUrl> &list);
    void sortList(bool asc);

    MediaDataItem at(int row);
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override ;

signals:
    void songListChanged();
//    void sourceChanged(QString);

private:
    QList<MediaDataItem> mData;
    QHash<int, QByteArray> mRoleNames;
};

#endif // MEDIADATALIST_H
