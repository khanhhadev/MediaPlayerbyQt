#include "languageset.h"
#include <QTranslator>

void LanguageSet::setLanguage(QApplication* app, QQmlApplicationEngine* engine, QString lang)
{
    static bool first = true;
    static QTranslator translator;
    if (!first) app->removeTranslator(&translator);
    qDebug() << translator.load(lang, ":/languages");
    app->installTranslator(&translator);
    if (!first) engine->retranslate();
    first = false;
}
