#include <QDebug>
//#include <QFileDialog>
#include <QFile>
//#include <QStandardPaths>

#include "Model/mediadatalist.h"

MediaDataList::MediaDataList(QObject *parent)
    : QAbstractListModel(parent)
{
    mRoleNames[SourceRole] = "source";
    mRoleNames[NameRole] = "name";
    mRoleNames[AlbumTitleRole] = "album";
    mRoleNames[ContributingArtistRole] = "artist";
    mRoleNames[DateRole] = "date";
}

int MediaDataList::count() const
{
    return mData.length();
}

int MediaDataList::rowCount(const QModelIndex &parent = QModelIndex()) const
{
    if (parent.isValid()) return 0;
    return count();
}

QVariant MediaDataList::data(const QModelIndex &index, int role) const
{

    if(index.isValid() == false) return QVariant();
    return mData.at(index.row()).getValue(role);

}

void MediaDataList::addNewFiles(const QUrl &file)
{
    MediaDataItem temp(file);
    auto itr = std::find(mData.begin(), mData.end(), temp);
    if (itr == mData.end())
    {
        beginInsertRows(QModelIndex(), count(), count());
        mData.append(temp);
        endInsertRows();
    }
}

void MediaDataList::addNewFiles(const QList<QUrl> &list)
{
//    static int count = 0;
    for (QUrl itemurl : list)
    {
        addNewFiles(itemurl);
//        emit sourceChanged(at(count).getValue(Roles::SourceRole));
//        qDebug() << __FUNCTION__ << ++count;
    }
}

MediaDataItem MediaDataList::at(int row)
{
    return mData.at(row);
}

void MediaDataList::clear()
{
    mData.clear();
    emit layoutChanged();
    qDebug() << __FUNCTION__ << mData.length();
}

void MediaDataList::sortList(bool asc)
{
    if (asc)
    {
        std::sort(mData.begin(), mData.end());
    }
    else
    {
        std::reverse(mData.begin(), mData.end());
    }
    emit layoutChanged();
}

QHash<int, QByteArray> MediaDataList::roleNames() const
{
    return mRoleNames;
}

