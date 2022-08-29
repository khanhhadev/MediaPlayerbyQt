/***********************************************
*THIS CLASS IS USED TO READ & wRITE BACKUP
*BEFORE APPLICATION CLOSES
************************************************/

#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <QObject>
#include <QStandardPaths>

class DataStorage
{
public:
    static QString readBackup(QString& language);
    static void writeBackup(QString mDirectory, QString& language);
private:
    static QString mDataFileLocation;
};

#endif // DATASTORAGE_H
