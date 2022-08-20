#ifndef LANGUAGESET_H
#define LANGUAGESET_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>

class LanguageSet : public QObject
{
    Q_OBJECT
public:
    explicit LanguageSet(QApplication *main = nullptr,
                         QQmlApplicationEngine* engine = nullptr,
                         QObject *parent = nullptr);
    virtual ~LanguageSet(){}
    void setLanguage(QString lang);
    void setLang(const QString lang);
signals:
    void languageChanged();

public slots:
    void languageUpdate();
private:
    QString mLanguage;
    QApplication& mApp;
    QQmlApplicationEngine& mEngine;
};

#endif // LANGUAGESET_H
