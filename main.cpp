#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>
#include <QFileDialog>
#include <QtQuick>
#include <QIcon>

#include "controls/mediacontrol.h"
//#include "controls/Support/datastorage.h"
#include "models/player.h"
#include "models/playlist.h"
#include "models/subelements/imageitem.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/image/music.png"));
    PlayList myData;
    Player myPlayer;
    MediaControl* myControl = nullptr;

    QQmlApplicationEngine engine;
    qmlRegisterType<ImageItem>("CustomImage", 1, 0, "ImageItem");
    myControl = new  MediaControl(&myPlayer, &myData, &app, &engine);

    QQmlContext *appRootContext = engine.rootContext();
    appRootContext->setContextProperty("myPlayer", &myPlayer);
    appRootContext->setContextProperty("myData", &myData);
    appRootContext->setContextProperty("myControl", myControl);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    app.exec();
    myControl->backup();
    return 1;
}
