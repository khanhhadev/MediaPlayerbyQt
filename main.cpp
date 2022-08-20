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
    app.setWindowIcon(QIcon(":/image/music.png"));

    MediaDataList myData;
    Player myPlayer;
    MediaControl* myControl;

    QQmlApplicationEngine engine;
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
