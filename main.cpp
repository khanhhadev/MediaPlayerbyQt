#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QQmlContext>
#include <QFileDialog>
#include <QThread>
#include <QTranslator>

#include "mediacontrol.h"
#include "player.h"
#include "mediadatalist.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QTranslator translator;
    MediaDataList myData;
    Player myPlayer;
    MediaControl myControl(&myPlayer, &myData);
    app.setWindowIcon(QIcon(":/image/music.png"));

    QQmlApplicationEngine engine;
    QQmlContext *appRootContext = engine.rootContext();
    appRootContext->setContextProperty("myControl", &myControl);
    appRootContext->setContextProperty("myPlayer", &myPlayer);
    appRootContext->setContextProperty("myData", &myData);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    QObject *object = engine.rootObjects().at(0);

    return app.exec();
}
