#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tunerlistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // register our TunerListModel so it can be used from QML
    qmlRegisterType<TunerListModel>("TunerListModel", 1, 0, "TunerListModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

