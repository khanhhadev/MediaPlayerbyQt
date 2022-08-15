#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include "mediadatalist.h"
#include "browserdialog.h"
#include "player.h"
#include <QObject>

class MediaControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)

public:
    explicit MediaControl(Player *player, MediaDataList* songlist, QObject *parent = nullptr);

    void makeConnect();

    //mDirectory READ-WRITE function
    void setDirectory(const QString dir);
    QString getDirectory() const;

    //mcurrentIndex READ-WRITE function
    int getCurrentIndex() const;
    void setCurrentIndex(const int currentIndex);

    void setSource(QString source);
    void connectToView(QObject *object);
signals:
    void directoryChanged();
    void currentIndexChanged();
    void listEnded();
    void sourceChanged(QString source);

public slots:
    void onDirectoryChanged(QString path, QList<MediaDataItem> newlist);
    void onListEnded();
    void onEndOfSong();
    void onCurrentIndexChanged();

    void selectSong(int index);
    void nextSong();
    void previousSong();
    void playpause();
    void changeMute();
    void changeRepeat();
    void changeDirectory();
    void addFiles();
    void sortList();
private:
    //MEDIA PLAYER
    Player* myPlayer;

    //PLAYLIST
    MediaDataList* myData;

    //FOLDER DIALOG
    BrowserDialog myBrowser;

    int mCurrentIndex;
    QString mDirectory;
    const QString mDataFileLocation = (QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/MusicPlayer");

    //FUNCTION
    void readBackup();
    void writeBackup();
};

#endif // MEDIACONTROL_H
