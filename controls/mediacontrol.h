/***********************************************
*USED TO CONTROL ALL APPLICATION PROCESS
************************************************/

#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "controls/Support/browserdialog.h"
#include "controls/Support/setting.h"
#include "controls/Support/languageset.h"
#include "models/playlist.h"
#include "models/player.h"

class MediaControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(bool shuffle READ shuffle WRITE setShuffle NOTIFY shuffleChanged)
public:
    explicit MediaControl(Player *player, PlayList* songlist,
                          QApplication *main = nullptr, QQmlApplicationEngine* engine = nullptr,
                          QObject *parent = nullptr);

    //make connect application modules
    void makeConnect();
    void backup();

    //mDirectory READ-WRITE function
    void setDirectory(const QString dir);
    QString getDirectory() const;

    //mcurrentIndex READ-WRITE function
    int currentIndex() const;
    void setCurrentIndex(const int currentIndex);

//    //set source to mediaplayer object
//    void setSource(QString source);

    //FUNCTION CALLED FROM QML BY CLICKING BUTTON
    Q_INVOKABLE void selectSong(int index, bool doubleClick);
    Q_INVOKABLE void selectArtist(int index);
    Q_INVOKABLE void selectAlbum(int index);
    Q_INVOKABLE void nextSong();
    Q_INVOKABLE void previousSong();
    Q_INVOKABLE void playpause();
    Q_INVOKABLE void changeMute();
    Q_INVOKABLE void changeRepeat();
    Q_INVOKABLE void changeShuffle();
    Q_INVOKABLE void changeDirectory();
    Q_INVOKABLE void addFiles();
    Q_INVOKABLE void sortList(bool asc);
    Q_INVOKABLE void setLanguage(QString lang);
    Q_INVOKABLE void setMode(MODE newMode);
    Q_INVOKABLE void addFavourite(int index);
    Q_INVOKABLE void retranslate();
    bool shuffle() const;
    void setShuffle(bool newShuffle);

signals:
    void listEnded();
    void shuffleChanged();
    void directoryChanged();
    void currentIndexChanged();
    void sourceChanged(QString source);

public slots:
    void onListEnded();
    void onEndOfSong();
    void onCurrentIndexChanged();
    void onDirectoryChanged(bool clear, QString path, QList<QUrl> newlist);

private:
    //MEDIA PLAYER
    Player* myPlayer;

    //PLAYLIST
    PlayList* myData;

    //FOLDER DIALOG
    BrowserDialog myBrowser;

    //LANGUAGE SETTING
    LanguageSet myLanguage;

    Setting mySetting;

    bool mShuffle;
    int mCurrentIndex;
    QString mDirectory;

    //FUNCTION
    void nextArtist();

};

#endif // MEDIACONTROL_H
