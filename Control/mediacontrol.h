#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "Control/Support/browserdialog.h"
#include "Control/Support/datastorage.h"
#include "Model/mediadatalist.h"
#include "Model/player.h"

class MediaControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(bool shuffle READ shuffle WRITE setShuffle NOTIFY shuffleChanged)
public:
    explicit MediaControl(Player *player, MediaDataList* songlist, QApplication* main, QObject *parent = nullptr);

    void makeConnect();
    void backup();

    //mDirectory READ-WRITE function
    void setDirectory(const QString dir);
    QString getDirectory() const;

    //mcurrentIndex READ-WRITE function
    int currentIndex() const;
    void setCurrentIndex(const int currentIndex);

    void setSource(QString source);

    void getEngineRef(QQmlApplicationEngine* en);

    Q_INVOKABLE void selectSong(int index);
    Q_INVOKABLE void nextSong();
    Q_INVOKABLE void previousSong();
    Q_INVOKABLE void playpause();
    Q_INVOKABLE void changeMute();
    Q_INVOKABLE void changeRepeat();
    Q_INVOKABLE void changeShuffle();
    Q_INVOKABLE void changeDirectory();
    Q_INVOKABLE void addFiles();
    Q_INVOKABLE void sortList();
    Q_INVOKABLE void setLanguage(int lang);

    bool shuffle() const;
    void setShuffle(bool newShuffle);

signals:
    void directoryChanged();
    void currentIndexChanged();
    void listEnded();
    void sourceChanged(QString source);

    void shuffleChanged();

public slots:
    void onDirectoryChanged(QString path, QList<QUrl> newlist);
    void onListEnded();
    void onEndOfSong();
    void onCurrentIndexChanged();

private:
    //MEDIA PLAYER
    Player* myPlayer;

    //PLAYLIST
    MediaDataList* myData;

    //FOLDER DIALOG
    BrowserDialog myBrowser;

    bool mShuffle;
    int mCurrentIndex;
    QString mDirectory;

    QApplication* app;
    QQmlApplicationEngine* engine;

};

#endif // MEDIACONTROL_H
