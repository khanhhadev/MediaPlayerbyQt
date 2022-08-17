#ifndef LANGUAGESET_H
#define LANGUAGESET_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>

class LanguageSet
{
public:
    static void setLanguage(QApplication* app, QQmlApplicationEngine* engine, QString lang);
};

#endif // LANGUAGESET_H
