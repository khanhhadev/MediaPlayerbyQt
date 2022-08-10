#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QQmlContext>
#include <QFileDialog>
#include <QThread>

#include "mediacontrol.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    MediaControl myControl;
    app.setWindowIcon(QIcon(":/image/music.png"));

    QQmlApplicationEngine engine;
    QQmlContext *appRootContext = engine.rootContext();
    appRootContext->setContextProperty("myControl", &myControl);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    QObject *object = engine.rootObjects().at(0);

    QObject::connect(object, SIGNAL(qmlChangeDirectory())
                     , &myControl ,SLOT(onChangingDirectory()));

    return app.exec();
}
