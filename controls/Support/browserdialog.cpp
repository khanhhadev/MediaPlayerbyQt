#include "controls/Support/browserdialog.h"
#include <QFile>
#include <QComboBox>
#include <QDirIterator>

BrowserDialog::BrowserDialog(QWidget *parentW, QObject *parent)
    : QObject{parent}, mBrowser(parentW)
{
    qDebug() << __FUNCTION__;
    mBrowser.setNameFilter("*.mp3 *.wav *.mid *.aif");
    mBrowser.setFilter(QDir::Dirs);
    mBrowser.setViewMode(QFileDialog::List);
    mBrowser.setOption(QFileDialog::ReadOnly, true);
    mBrowser.setAcceptMode(QFileDialog::AcceptOpen);

    QObject::connect(&mBrowser, &QFileDialog::accepted, this, &BrowserDialog::onAccepted);
    QObject::connect(&mBrowser, &QFileDialog::urlsSelected, this, &BrowserDialog::onAccepted);
}

//get list of song fromt directory url
void BrowserDialog::getListFromFolder(QUrl path, bool& clear)
{
    qDebug() << __FUNCTION__ << path;
    QDir directory(path.toLocalFile());
    QDirIterator  it(path.toLocalFile(), QDir::Dirs|QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QString absoPath = it.path();
    while(it.hasNext()){
        absoPath = it.next();
        getListFromFolder(QUrl::fromLocalFile(absoPath), clear);
    }
    QList<QUrl> itemurls;
    QStringList sourcelist  = directory.entryList(QStringList() << "*.wav" << "*.mid" << "*.aif" << "*.mp3", QDir::Files);
    for (QString& song: sourcelist)
    {
        itemurls << QUrl::fromLocalFile(path.toLocalFile() + "/"+ song);
    }
    emit directoryChanged(clear, path.toString(), itemurls);
    clear = false;
}

//open browser dialog to select folder
void BrowserDialog::changeDirectory(QString directory)
{
    mReadMode = READMODE::READFOLDER;
    mBrowser.setFileMode(QFileDialog::Directory);
    mBrowser.setDirectoryUrl(QUrl::fromLocalFile(directory));
    mBrowser.exec();
}


//open browser dialog to select files
void BrowserDialog::addFiles(QString directory)
{
    mReadMode = READMODE::READFILES;
    mBrowser.setFileMode(QFileDialog::ExistingFiles);
    mBrowser.setDirectoryUrl(QUrl::fromLocalFile(directory));
    mBrowser.exec();
}

void BrowserDialog::onAccepted()
{

    switch (mReadMode) {
    case READMODE::READFOLDER:
    {
        bool clear = true;
        getListFromFolder(mBrowser.directoryUrl(), clear);
    }
        break;
    case READMODE::READFILES:
    {
        QList<QUrl> files = mBrowser.selectedUrls();
        emit directoryChanged(false, mBrowser.directoryUrl().toString(), files);
    }
        break;
    default:
        break;
    }

}
