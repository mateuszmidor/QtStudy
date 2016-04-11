#include <QApplication>
#include <QQmlApplicationEngine>
#include "pythonhighlighter.h"
#include <QQuickTextDocument>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* pythonEdit = engine.rootObjects().at(0)->findChild<QObject*>("pythonEdit");
    QQuickTextDocument* doc = qvariant_cast<QQuickTextDocument*>(pythonEdit->property("textDocument"));
    PythonHighlighter hl(doc->textDocument());
    return app.exec();
}

