#include <QTranslator>
#include <QRandomGenerator>

#include "Control/mediacontrol.h"
#include "Model/mediadatalist.h"
#include "Control/Support/datastorage.h"
#include "Control/Support/languageset.h"
#include "Control/Support/browserdialog.h"

MediaControl::MediaControl(Player *player, MediaDataList* songlist,
                           QApplication *main, QQmlApplicationEngine* engine,
                           QObject *parent)
    : QObject{parent}, myPlayer(player), myData(songlist),
      mShuffle(false), myLanguage(main, engine)
{
    makeConnect();
    QString mLanguage;
    setDirectory(DataStorage::readBackup(mLanguage));
    myLanguage.setLang(mLanguage);
    myBrowser.getListFromFolder(QUrl(mDirectory));
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

    //    QObject::connect(this, &MediaControl::sourceChanged,
    //                     this->myPlayer, &Player::onSourceChanged);

    QObject::connect(this->myData, &MediaDataList::sourceChanged,
                     this->myPlayer, &Player::onSourceChanged);
}

void MediaControl::backup()
{
//    DataStorage::writeBackup(mDirectory, mLanguage);
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

void MediaControl::selectSong(int index)
{
    setCurrentIndex(index);
    if (mCurrentIndex >= 0)
    {
        QMediaPlayer::PlaybackState temp = myPlayer->getState();
        myPlayer->setSource(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
        myPlayer->setState(temp);
    }
}

void MediaControl::nextSong()
{
    if (mCurrentIndex < myData->count() - 1)
    {
        QMediaPlayer::PlaybackState temp = myPlayer->getState();
        if (mShuffle) setCurrentIndex(rand() % myData->count());
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
        if (mShuffle) setCurrentIndex(rand() % myData->count());
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

void MediaControl::onDirectoryChanged(QString path, QList<QUrl> newlist)
{
    setDirectory(path);
    myData->addNewFiles(newlist);
    setCurrentIndex(-1);
    qDebug() << __FUNCTION__ << myData->count();
}

void MediaControl::changeDirectory()
{
    myData->clear();
    setCurrentIndex(-1);
    myBrowser.changeDirectory(mDirectory);
}

void MediaControl::addFiles()
{
    myBrowser.addFiles(mDirectory);
}

void MediaControl::sortList()
{
    myPlayer->stop();
    setCurrentIndex(-1);
    static bool asc = true;
    myData->sortList(asc);
    asc = !asc;
}

void MediaControl::setLanguage(QString lang)
{
    myLanguage.setLanguage(lang);
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

//void MediaControl::getEngineRef(QQmlApplicationEngine *en)
//{
//    engine = en;
//    LanguageSet::setLanguage(app, engine, mLanguage);
//}


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
