#ifndef GUI
#define GUI

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include "sdarsqobject.h"

// Gui; loads and displays QML scene with qobject exposed, it runs on main thread
class Gui {
    // our qobject. it will be available from QML code
    SdarsQObject& qobject;

public:
    // constructor
    Gui(SdarsQObject& qobject) : qobject(qobject) {}

    // just load and show the QML scene in an QmlApplicationEngine
    int exec(int argc, char *argv[]) {
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;

        // expose our qobject to the qml engine under name "qobject"
        engine.rootContext()->setContextProperty("qobject", &qobject);

        // load the QML scene
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        // run GUI event loop
        return app.exec();
    }
};

#endif // GUI
