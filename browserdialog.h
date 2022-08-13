/***********************************************
*THIS CLASS IS USED TO CREATE FOLDER DIALOG
*TO SELECT FOLDER TO PLAY SONG LIST
************************************************/

#ifndef BROWSERDIALOG_H
#define BROWSERDIALOG_H

#include <QObject>
#include <QApplication>
#include <QFileDialog>
#include <QUrl>
#include "mediadatalist.h"

class BrowserDialog : public QObject
{
    Q_OBJECT

public:
    explicit BrowserDialog(QWidget *parentW = nullptr,QObject *parent = nullptr);
    QList<MediaDataItem> getListFromFolder(QUrl path);
private:
    QFileDialog mBrowser;

signals:
    void directoryChanged(QString path, QList<MediaDataItem> newlist);

public slots:
    void changeDirectory(QString directory);
    void addFiles(QString directory);
};

#endif // BROWSERDIALOG_H
