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
enum READMODE{
    READFILES,
    READFOLDER
};

class BrowserDialog : public QObject
{
    Q_OBJECT
public:
    explicit BrowserDialog(QWidget *parentW = nullptr, QObject *parent = nullptr);

    //get list of song fromt directory url
    void getListFromFolder(QUrl path, bool& clear);

private:
    QFileDialog mBrowser;
    READMODE mReadMode;

signals:
    void directoryChanged(bool clear, QString path, QList<QUrl> files);

public slots:
    //open browser dialog to select folder
    void changeDirectory(QString directory);

    //open browser dialog to select files
    void addFiles(QString directory);
    void onAccepted();
};

#endif // BROWSERDIALOG_H
