#include "Control/Support/datastorage.h"
#include <QDir>
#include <QUrl>
#include <QIODevice>

QString DataStorage::mDataFileLocation =
        (QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/MusicPlayer");

QString DataStorage::readBackup(QString& language)
{
    //    QUrl path = QUrl::fromLocalFile(mDataFileLocation);
    QDir dir(mDataFileLocation);
    if (!dir.exists()) dir.mkpath(".");

    QString line = "";
    qDebug() << __FUNCTION__ << mDataFileLocation;
    QFile DataFile(mDataFileLocation + "/AppData.txt");
    if (DataFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&DataFile);
//        while (!stream.atEnd())
//        {
            line = stream.readLine();
            qDebug() << __FUNCTION__ << line;
//            stream.readLine();s
            language = stream.readLine();
            qDebug() << __FUNCTION__ << language;
//        }
        DataFile.close();

    }
    if (line == "") line = mDataFileLocation;
    qDebug() << language;
    return line;
}

void DataStorage::writeBackup(QString mDirectory, QString& language)
{
    QFile DataFile(mDataFileLocation + "/AppData.txt");
    qDebug() << "write" << mDirectory;
    if (DataFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << __FUNCTION__ << mDirectory;
        QTextStream stream(&DataFile);
        stream << QString(mDirectory)+'\n' + language;
        DataFile.flush();
        DataFile.close();
        qDebug() << "writed" << mDirectory << language;
    }
}
