#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "pythoninterpreter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // python interpreter QObject to be exposed in QML
    PythonInterpreter _python;

    // expose our qobject to the qml engine under name "_python"
    engine.rootContext()->setContextProperty("_python", &_python);

    // load the scene
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // run the event loop
    return app.exec();
}

