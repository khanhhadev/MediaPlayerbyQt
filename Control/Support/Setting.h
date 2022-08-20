#ifndef SETTING_H
#define SETTING_H
#include <QtGui/QGuiApplication>
#include <QFile>
#include <QSettings>
#include <QTextStream>
#include <QQmlContext>

class Setting : public QObject
{
    Q_OBJECT
public slots:
    void updateSetting(QString type, int mode){
        QString settingPath = QGuiApplication::applicationDirPath() + "/config.ini";
        QSettings settings(settingPath, QSettings::IniFormat);
        settings.setValue(type, mode);
    }


    int getSetting(QString mode){
        QString settingPath = QGuiApplication::applicationDirPath() + "/config.ini";
        QSettings settings(settingPath, QSettings::IniFormat);
        if(!QFile::exists(settingPath))
        {
            settings.setValue("language", "0");
            settings.setValue("theme", "0");
        }
        else
        {
            return settings.value(mode).toInt();
        }
        return 0;
    }
};

#endif // SETTING_H
