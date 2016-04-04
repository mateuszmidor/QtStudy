#ifndef GUI
#define GUI

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>

// Gui loads and displays QML scene, it runs on main thread
class Gui : public QObject {
    Q_OBJECT
    QObject *label;

public:

    // just run load and show the QML scene in an QmlApplicationEngine
    int exec(int argc, char *argv[]) {
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        label = engine.rootObjects().at(0)->findChild<QObject*>("label");
        return app.exec();
    }

public slots:

    // display the command on as label text
    void onCommand(const QString &cmd) {
        label->setProperty("text", (cmd));
    }
};

#endif // GUI

