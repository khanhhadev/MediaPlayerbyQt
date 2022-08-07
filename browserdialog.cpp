#include "browserdialog.h"

BrowserDialog::BrowserDialog(QWidget *parentW, QObject *parent)
    : QObject{parent}, mBrowser(parentW)
{
    mBrowser.setNameFilter("*.mp3 *.mp4");
    mBrowser.setFilter(QDir::AllEntries);
    mBrowser.setFileMode(QFileDialog::Directory);
    mBrowser.setOption(QFileDialog::ReadOnly, true);
    mBrowser.setAcceptMode(QFileDialog::AcceptOpen);


}

void BrowserDialog::changeDirectory(QString directory)
{
    mBrowser.setDirectoryUrl(QUrl::fromLocalFile(directory));
    mBrowser.exec();
    emit changingDirectory(mBrowser.directoryUrl().toString());
    qDebug() <<__FUNCTION__<< mBrowser.directoryUrl().toString();
}
