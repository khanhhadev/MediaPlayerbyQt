#include "mediacontrol.h"

#include "mediadatalist.h"
#include "browserdialog.h"

MediaControl::MediaControl(Player *player, MediaDataList* songlist, QObject *parent)
    : QObject{parent}, myPlayer(player), myData(songlist)/*, mCurrentIndex(-1)*/
{
    makeConnect();
    readBackup();
    setCurrentIndex(0);
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

int MediaControl::getCurrentIndex() const
{
    return mCurrentIndex;
}

void MediaControl::setCurrentIndex(const int currentIndex)
{
    if (currentIndex < myData->count())
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
        setCurrentIndex(mCurrentIndex + 1);
        myPlayer->setSource(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
        myPlayer->setState(temp);
    } else {
        emit listEnded();
        //        myPlayer->stop();
        //        myPlayer->setPosition(myPlayer->getDuration());
    }
}

void MediaControl::previousSong()
{
    if (mCurrentIndex > 0)
    {
        QMediaPlayer::PlaybackState temp = myPlayer->getState();
        setCurrentIndex(mCurrentIndex - 1);
        myPlayer->setSource(myData->at(mCurrentIndex).getValue(Roles::SourceRole));
        myPlayer->setState(temp);
    } else {
        myPlayer->stop();
        myPlayer->setPosition(0);
    }
}

void MediaControl::playpause()
{
    if(myPlayer->getState() == QMediaPlayer::PlayingState) myPlayer->pause();
    else myPlayer->play();
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

void MediaControl::onDirectoryChanged(QString path, QList<MediaDataItem> newlist)
{
    setDirectory(path);
    myData->addNewFiles(newlist);
    setCurrentIndex(0);
    writeBackup();
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
    myData->sortList(true);
}

void MediaControl::connectToView(QObject *object)
{
    connect(object, SIGNAL(qmlselectSong(int))
            , this ,SLOT(selectSong(int)));
    connect(object, SIGNAL(qmlnextSong())
            , this ,SLOT(nextSong()));
    connect(object, SIGNAL(qmlpreviousSong())
            , this ,SLOT(previousSong()));
    connect(object, SIGNAL(qmlplaypause())
            , this ,SLOT(playpause()));
    connect(object, SIGNAL(qmlchangeMute())
            , this ,SLOT(changeMute()));
    connect(object, SIGNAL(qmlchangeRepeat())
            , this ,SLOT(changeRepeat()));
    connect(object, SIGNAL(qmlchangeDirectory())
            , this ,SLOT(changeDirectory()));
    connect(object, SIGNAL(qmladdFiles())
            , this ,SLOT(addFiles()));
    connect(object, SIGNAL(qmlsortList())
            , this ,SLOT(sortList()));
}

void MediaControl::onListEnded()
{
    myPlayer->stop();
    myPlayer->setPosition(myPlayer->getDuration());
}

void MediaControl::onEndOfSong()
{
    if (mCurrentIndex < myData->count() - 1)
    {
        setCurrentIndex(mCurrentIndex + 1);
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
}

void MediaControl::readBackup()
{
    QUrl path = mDataFileLocation;
    QDir dir(path.toLocalFile());
    if (!dir.exists()) dir.mkpath(".");
    QFile DataFile(mDataFileLocation + "/AppData.txt");
    if (DataFile.open(QIODevice::ReadWrite))
    {
        QString line = DataFile.readLine();
        if (line != "") setDirectory(line);
        else setDirectory(mDataFileLocation);
        DataFile.close();
    }
}

void MediaControl::writeBackup()
{
    QFile DataFile(mDataFileLocation + "/AppData.txt");
    qDebug() << "write" << mDirectory;
    if (DataFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&DataFile);
        stream << QString(mDirectory);
        DataFile.flush();
        DataFile.close();
        qDebug() << "writed" << mDirectory;
    }
}
