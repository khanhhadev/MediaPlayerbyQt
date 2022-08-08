#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QQmlContext>
#include <QFileDialog>

#include "mediadata.h"
#include "player.h"
#include "browserdialog.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    MediaData myData;
    Player myPlayer;

    BrowserDialog myBrowser;
    app.setWindowIcon(QIcon(":/image/music.png"));
    QObject::connect(&myData, &MediaData::sourceChanged
                     ,&myPlayer, &Player::onSourceChanged);

    QObject::connect(&myBrowser, &BrowserDialog::changingDirectory,
                     &myData, &MediaData::onChangingDirectory);

    QObject::connect(&myPlayer, &Player::endOfSong,
                     &myData, &MediaData::nextSong);

    QQmlApplicationEngine engine;
    QQmlContext *appRootContext = engine.rootContext();

    appRootContext->setContextProperty("myData", &myData);
    appRootContext->setContextProperty("myPlayer", &myPlayer);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    QObject *object = engine.rootObjects().at(0);
    QObject::connect(object, SIGNAL(qmlChangeDirectory(QString))
                     , &myBrowser ,SLOT(changeDirectory(QString)));

    return app.exec();
}
