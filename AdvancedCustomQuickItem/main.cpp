#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "barchartitem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // register our BarItem and BarChart before loading the scene
    qmlRegisterType<BarItem>("Shapes", 1, 0, "Bar");
    qmlRegisterType<BarChartItem>("Shapes", 1, 0, "BarChart");

    // load the qml scene
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // run the app
    return app.exec();
}

