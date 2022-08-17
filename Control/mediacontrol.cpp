#include <QTranslator>
#include <QRandomGenerator>

#include "Control/mediacontrol.h"
#include "Model/mediadatalist.h"
#include "Control/Support/browserdialog.h"

MediaControl::MediaControl(Player *player, MediaDataList* songlist, QApplication *main, QObject *parent)
    : QObject{parent}, myPlayer(player), myData(songlist), app(main), mShuffle(false)
{
    makeConnect();
    QString n;
    setDirectory(DataStorage::readBackup(n));
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

    QObject::connect(this, &MediaControl::sourceChanged,
                     this->myPlayer, &Player::onSourceChanged);
}

void MediaControl::backup()
{
    QString n;
    DataStorage::writeBackup(mDirectory, n);
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

void MediaControl::setLanguage(int lang)
{
    static QTranslator translator;
    static QString LangFile;
    if (LangFile!= "")
        app->removeTranslator(&translator);
    switch (lang) {
    case 1:
        LangFile = "mediaplayer_vi.qm";
        break;
    case 2:
        LangFile = "mediaplayer_en.qm";
        break;
    case 3:
        LangFile = "mediaplayer_jp.qm";
        break;
    default:
        break;
    }
    qDebug() << translator.load(LangFile, app->applicationDirPath());
    app->installTranslator(&translator);
    if (LangFile != "") engine->retranslate();
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

void MediaControl::getEngineRef(QQmlApplicationEngine *en)
{
    engine = en;
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
