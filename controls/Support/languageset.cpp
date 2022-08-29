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
    qDebug() << __FUNCTION__ << "is First:" << first;
    static QTranslator translator;
    if (mLanguage != lang) setLang(lang);
    qDebug() << translator.load(lang, ":/languages");
    /*mApp.*/QCoreApplication::instance()->installTranslator(&translator);
    /*if (!first) */mEngine.retranslate();
    first = false;
}

QString& LanguageSet::language()
{
    return mLanguage;
}

//set new language
void LanguageSet::setLang(const QString lang)
{
    if (lang != mLanguage)
    {
        mLanguage = lang;
    }
}

//update app language when new component was created
void LanguageSet::languageUpdate()
{
    qDebug() << __FUNCTION__ << mLanguage;
    mEngine.retranslate();
}
