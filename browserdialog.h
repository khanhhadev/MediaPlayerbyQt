#ifndef BROWSERDIALOG_H
#define BROWSERDIALOG_H

#include <QObject>
#include <QApplication>
#include <QFileDialog>

class BrowserDialog : public QObject
{
    Q_OBJECT
public:
    explicit BrowserDialog(QWidget *parentW = nullptr,QObject *parent = nullptr);

private:
    QFileDialog mBrowser;

signals:
    void changingDirectory(QString path);

public slots:
    void changeDirectory(QString directory);
};

#endif // BROWSERDIALOG_H
