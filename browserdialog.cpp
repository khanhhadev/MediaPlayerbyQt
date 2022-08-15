#include "browserdialog.h"
#include <QFile>
#include <QComboBox>

BrowserDialog::BrowserDialog(QWidget *parentW, QObject *parent)
    : QObject{parent}, mBrowser(parentW)
{
    mBrowser.setNameFilter("*.mp3 *.wav *.mid *.aif");
    mBrowser.setFilter(QDir::Dirs);
    //    mBrowser.setFilter(QDir::Files);
    //        mBrowser.setOption(QFileDialog::DontUseNativeDialog,true);
    //    mBrowser.setOption(QFileDialog::DontResolveSymlinks);
    mBrowser.setViewMode(QFileDialog::List);
    mBrowser.setOption(QFileDialog::ReadOnly, true);
    mBrowser.setAcceptMode(QFileDialog::AcceptOpen);

}

QList<MediaDataItem> BrowserDialog::getListFromFolder(QUrl path)
{
    QDir directory(path.toLocalFile());
    QStringList sourcelist  = directory.entryList(QStringList() << "*.wav" << "*.mid" << "*.aif" << "*.mp3",QDir::Files);
    QList<MediaDataItem> data;
    for (QString& song: sourcelist)
    {
        data.append(MediaDataItem(path.toString() + "/" + song, song));
    }
    emit directoryChanged(path.toString(), data);
    return data;
}

//open browser dialog to select folder
void BrowserDialog::changeDirectory(QString directory)
{
    mBrowser.setFileMode(QFileDialog::Directory);
    mBrowser.setDirectoryUrl(QUrl::fromLocalFile(directory));
    mBrowser.exec();
    getListFromFolder(mBrowser.directoryUrl());
    qDebug() << __FUNCTION__ << mBrowser.directoryUrl().toString();
}

void BrowserDialog::addFiles(QString directory)
{
    mBrowser.setFileMode(QFileDialog::ExistingFiles);
    mBrowser.setDirectoryUrl(QUrl::fromLocalFile(directory));
    mBrowser.exec();
    QList<QUrl> files = mBrowser.selectedUrls();
    QList<MediaDataItem> data;
    for (QUrl& song: files)
    {
        data.append(MediaDataItem(song.toString(), song.fileName()));
        qDebug() << __FUNCTION__ << song.toString() << song.fileName();
    }
    emit directoryChanged(mBrowser.directoryUrl().toString(), data);
}
