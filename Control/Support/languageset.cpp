#include "languageset.h"
#include <QTranslator>

LanguageSet::LanguageSet(QApplication *main, QQmlApplicationEngine* engine, QObject *parent)
    : QObject(parent), mApp(*main), mEngine(*engine)
{
//    QObject::connect(this, &LanguageSet::languageChanged,
//                     this, &LanguageSet::languageUpdate);
}

void LanguageSet::setLanguage(QString lang)
{
    static bool first = true;
    static QTranslator translator;
    if (lang != mLanguage)
    {
        setLanguage(lang);
        if (!first) mApp.removeTranslator(&translator);
        qDebug() << translator.load(lang, ":/languages");
        mApp.installTranslator(&translator);
        if (!first) mEngine.retranslate();
        first = false;
    }
}

void LanguageSet::setLang(const QString lang)
{
    if (lang != mLanguage)
    {
        mLanguage = lang;
//        emit languageChanged();
    }
}

void LanguageSet::languageUpdate()
{

}
