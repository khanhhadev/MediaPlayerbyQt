#include "Control/Support/browserdialog.h"
#include <QFile>
#include <QComboBox>

BrowserDialog::BrowserDialog(QWidget *parentW, QObject *parent)
    : QObject{parent}, mBrowser(parentW)
{
    mBrowser.setNameFilter("*.mp3 *.wav *.mid *.aif");
    mBrowser.setFilter(QDir::Dirs);
    mBrowser.setViewMode(QFileDialog::List);
    mBrowser.setOption(QFileDialog::ReadOnly, true);
    mBrowser.setAcceptMode(QFileDialog::AcceptOpen);
}

void BrowserDialog::getListFromFolder(QUrl path)
{
    QDir directory(path.toLocalFile());

    QStringList sourcelist  = directory.entryList(QStringList() << "*.wav" << "*.mid" << "*.aif" << "*.mp3",QDir::Files);
    QList<QUrl> itemurls;
    for (QString& song: sourcelist)
    {
        itemurls.append(QUrl(path.toLocalFile() + "/"+ song));
    }
    emit directoryChanged(path.toString(), itemurls);
    qDebug() << itemurls;
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
    emit directoryChanged(mBrowser.directoryUrl().toString(), files);
}
