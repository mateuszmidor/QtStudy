#include <QtQml/QtQml>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

using namespace std;

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
