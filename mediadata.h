#ifndef MEDIADATA_H
#define MEDIADATA_H

#include <QObject>
#include <QFileSystemModel>
#include <QUrl>
#include <QStandardPaths>

class MediaData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList songList READ getSongList WRITE setSongList NOTIFY songListChanged)
    Q_PROPERTY(QString directory READ getDirectory WRITE setDirectory NOTIFY directoryChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
public:
    explicit MediaData(QObject *parent = nullptr);

    void getURLList(QUrl dir);

    void setDirectory(const QString dir);
    QString getDirectory() const;

    void setSongList(const QStringList newSongList);
    QStringList getSongList() const;

    int getCurrentIndex() const;
    void setCurrentIndex(const int currenIndex);

    Q_INVOKABLE QString getCurrentDirectory();

signals:
    void directoryChanged();
    void songListChanged();
    void sourceChanged(QString path);
    void currentIndexChanged(int currentindex);

public slots:
    void onDirectoryChanged();
    void onSongListChanged();
    void onCurrentIndexChanged(int currentindex);
    void onChangingDirectory(QString path);
private:
    QStringList mSongList;
    QString mDirectory;
    int mCurrentIndex;
    QString mDataFileLocation;
};

#endif // MEDIADATA_H
