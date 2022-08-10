#include "mediacontrol.h"

#include "mediadatalist.h"
#include "player.h"
#include "browserdialog.h"

MediaControl::MediaControl(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&myBrowser, &BrowserDialog::directoryChanged,
                     this, &MediaControl::onChangingDirectory);

    QObject::connect(&myPlayer, &Player::endOfSong,
                     this, &MediaControl::nextSong);

    readBackup();
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

void MediaControl::setSongList(const MediaDataList newSongList)
{

}

MediaDataList MediaControl::getSongList() const
{
    return myData;
}

int MediaControl::getCurrentIndex() const
{
    return mCurrentIndex;
}

void MediaControl::setCurrentIndex(const int currentIndex)
{
    if (mCurrentIndex != currentIndex)
    {
        mCurrentIndex = currentIndex;
        emit currentIndexChanged();
    }
}

void MediaControl::nextSong()
{
    if (mCurrentIndex < myData.count() - 1)
    {
        setCurrentIndex(mCurrentIndex + 1);
        myPlayer.play();
    } else myPlayer.stop()
}

void MediaControl::previousSong()
{

}

void MediaControl::directoryChanged()
{
    myData.addNewFolder(mDirectory);
    writeBackup();
}

void MediaControl::onChangingDirectory(QString path)
{
    Q_UNUSED(path);
    myBrowser.changeDirectory(mDirectory);
}

void MediaControl::onCurrentIndexChanged()
{
    myPlayer.setSource(myData.);
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
