#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QFileDialog>
#include <QtQuick>
#include <QIcon>

#include "Control/mediacontrol.h"
//#include "Control/Support/datastorage.h"
#include "Model/player.h"
#include "Model/mediadatalist.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    MediaDataList myData;
    Player myPlayer;
    MediaControl myControl(&myPlayer, &myData, &app);

    app.setWindowIcon(QIcon(":/image/music.png"));
    QQmlApplicationEngine engine;
    QQmlContext *appRootContext = engine.rootContext();
    appRootContext->setContextProperty("myControl", &myControl);
    appRootContext->setContextProperty("myPlayer", &myPlayer);
    appRootContext->setContextProperty("myData", &myData);

    myControl.getEngineRef(&engine);
//    myControl.setLanguage(1);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    app.exec();
    myControl.backup();
    return 1;
}
