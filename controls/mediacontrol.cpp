#include <QVariant>
#include <QTranslator>
#include <QRandomGenerator>

#include "controls/mediacontrol.h"
#include "models/playlist.h"
#include "controls/Support/languageset.h"
#include "controls/Support/browserdialog.h"

MediaControl::MediaControl(Player *player, PlayList* songlist,
                           QApplication *main, QQmlApplicationEngine* engine,
                           QObject *parent)
    : QObject{parent}, myPlayer(player), myData(songlist),
      myLanguage(main, engine), mShuffle(false)
{
    qDebug() << __FUNCTION__;
    makeConnect();
    mDirectory = mySetting.getSetting("directory").toString();
    myLanguage.setLanguage(mySetting.getSetting("language").toString());
    bool clear(true);
    myBrowser.getListFromFolder(QUrl(mDirectory), clear);
    myData->getFavouriteList(mySetting.getSetting("favourite").toStringList());
    setCurrentIndex(-1);
}

void MediaControl::makeConnect()
{
    QObject::connect(&myBrowser, &BrowserDialog::directoryChanged,
                     this, &MediaControl::onDirectoryChanged);

    QObject::connect(this->myPlayer, &Player::endOfSong,
                     this, &MediaControl::onEndOfSong);

    QObject::connect(this, &MediaControl::listEnded,
                     this, &MediaControl::onListEnded);

    QObject::connect(this->myData, &PlayList::sourceChanged,
                     this->myPlayer, &Player::onSourceChanged);
}

void MediaControl::backup()
{

}

void MediaControl::setDirectory(const QString dir)
{
    if (mDirectory != dir)
    {
        mDirectory = dir;
        emit directoryChanged();
    }
}

QString MediaControl::getDirectory() const
{
    return mDirectory;
}

int MediaControl::currentIndex() const
{
    return mCurrentIndex;
}

void MediaControl::setCurrentIndex(const int currentIndex)
{
    if ((currentIndex < myData->count()) && (currentIndex > -2))
    {
        if (mCurrentIndex != currentIndex)
        {
            mCurrentIndex = currentIndex;
            emit currentIndexChanged();
        }
    }
}

void MediaControl::selectSong(int index, bool doubleClick)
{
    setCurrentIndex(index);
    if (mCurrentIndex >= 0)
    {
        QMediaPlayer::PlaybackState temp = myPlayer->getState();
        myPlayer->setSource(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
        if (doubleClick) myPlayer->play();
        else myPlayer->setState(temp);
    }
}

void MediaControl::selectArtist(int index)
{
    if (index == myData->currentArtist()) return;
    myData->setCurrentArtist(index);
    setCurrentIndex(-1);
}

void MediaControl::selectAlbum(int index)
{
    if (index == myData->currentAlbum()) return;
    myData->setCurrentAlbum(index);
    setCurrentIndex(-1);
}

void MediaControl::nextSong()
{
    if (mCurrentIndex < myData->count() - 1)
    {
        QMediaPlayer::PlaybackState temp = myPlayer->getState();
        if (mShuffle) setCurrentIndex(rand() % (myData->count() - 1));
        else setCurrentIndex(mCurrentIndex + 1);
        myPlayer->setSource(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
        myPlayer->setState(temp);
    } else {
        emit listEnded();
    }
}

void MediaControl::previousSong()
{
    if (mCurrentIndex > 0)
    {
        QMediaPlayer::PlaybackState temp = myPlayer->getState();
        if (mShuffle) setCurrentIndex(rand() % (myData->count()-1));
        else setCurrentIndex(mCurrentIndex - 1);
        myPlayer->setSource(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
        myPlayer->setState(temp);
    } else {
        myPlayer->stop();
        myPlayer->setPosition(0);
    }
}

void MediaControl::playpause()
{
    if (myData->count() == 0) return;
    if (mCurrentIndex == -1)
    {
        setCurrentIndex(0);
        myPlayer->setSource(myData->at(0).getValue(Roles::SourceRole));
        myPlayer->play();
    }
    else
    {
        if (myPlayer->getState() == QMediaPlayer::PlayingState) myPlayer->pause();
        else myPlayer->play();
    }
    qDebug() << __FUNCTION__ << mCurrentIndex;
}

void MediaControl::changeMute()
{
    if (myPlayer->muted()) myPlayer->unmute();
    else myPlayer->mute();
}

void MediaControl::changeRepeat()
{
    if (myPlayer->repeat()) myPlayer->setRepeat(false);
    else myPlayer->setRepeat(true);
}

void MediaControl::changeShuffle()
{
    setShuffle(!mShuffle);
}

void MediaControl::onDirectoryChanged(bool clear, QString path, QList<QUrl> newlist)
{
    if (clear)
    {
        myData->clear();
        myPlayer->setSource("");
        myPlayer->stop();
        setCurrentIndex(-1);
    }
    setDirectory(path);
    mySetting.updateSetting("directory", mDirectory);
    myData->addNewFiles(newlist);
    qDebug() << __FUNCTION__ << myData->count();
}

void MediaControl::changeDirectory()
{
    myBrowser.changeDirectory(mDirectory);
}

void MediaControl::addFiles()
{
    myBrowser.addFiles(mDirectory);
}

void MediaControl::sortList(bool asc)
{
    myPlayer->stop();
    setCurrentIndex(-1);

    myData->sortList(asc);
}

void MediaControl::setLanguage(QString lang)
{
    qDebug() << __FUNCTION__ << lang;
    myLanguage.setLanguage(lang);
    mySetting.updateSetting("language", lang);
}

void MediaControl::setMode(MODE newMode)
{
    myData->setCurrentMode(newMode);
    setCurrentIndex(-1);
}

void MediaControl::addFavourite(int index)
{
    mySetting.updateSetting("favourite",QVariant::fromValue(myData->addFavourite(index)));
}

void MediaControl::retranslate()
{
    myLanguage.languageUpdate();
}

void MediaControl::onListEnded()
{
    myPlayer->stop();
    myPlayer->setPosition(myPlayer->duration());
}

void MediaControl::onEndOfSong()
{
    if (mCurrentIndex < myData->count() - 1)
    {
        if (mShuffle) setCurrentIndex(rand() % myData->count());
        else setCurrentIndex(mCurrentIndex + 1);
        myPlayer->setSource(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
        myPlayer->play();
    } else {
        emit listEnded();
    }
}
void MediaControl::onCurrentIndexChanged()
{
    if (mCurrentIndex != -1)
        emit sourceChanged(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
    else emit sourceChanged(myData->at(0).getValue(Roles::SourceRole));
}

void MediaControl::nextArtist()
{
    if (!myData->setCurrentArtist(myData->currentArtist() + 1))
        emit listEnded();
}


bool MediaControl::shuffle() const
{
    return mShuffle;
}

void MediaControl::setShuffle(bool newShuffle)
{
    if (mShuffle == newShuffle)
        return;
    mShuffle = newShuffle;
    emit shuffleChanged();
}
