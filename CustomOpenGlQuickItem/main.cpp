#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "openglitem.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // register our OpenGlItem so it can be used from QML
    qmlRegisterType<OpenGlItem>("OpenGl", 1, 0, "OpenGlItem");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

