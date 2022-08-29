/***********************************************
*USED TO SETTING PARAMETER FOR APPLICATION
************************************************/

#ifndef SETTING_H
#define SETTING_H
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QTextStream>
#include <QStandardPaths>
#include <QQmlContext>
#include <QVariant>

class Setting : public QObject
{
    Q_OBJECT
public slots:
    //update new setting to ini file
    void updateSetting(QString type, QVariant mode){
        QString settingPath = QApplication::applicationDirPath() + "/config.ini";
        QSettings settings(settingPath, QSettings::IniFormat);
        settings.setValue(type, mode);
    }

    //get backup setting from ini file
    QVariant getSetting(QString mode){
        QString settingPath = QApplication::applicationDirPath() + "/config.ini";
        QSettings settings(settingPath, QSettings::IniFormat);
        if(!QFile::exists(settingPath))
        {
            QStringList source = {};
            QString tmpDirectory = QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)).toString();
            settings.setValue("language", "mediaplayer_en.qm");
            settings.setValue("directory", tmpDirectory);
            settings.setValue("favourite", QVariant::fromValue(source));
        }
        return settings.value(mode);
    }
};

#endif // SETTING_H
