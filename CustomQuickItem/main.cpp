#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ellipseitem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // register our Ellipse befor loading the scene
    qmlRegisterType<EllipseItem>("Shapes", 1, 0, "Ellipse");

    // load the qml scene
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // run the app
    return app.exec();
}

