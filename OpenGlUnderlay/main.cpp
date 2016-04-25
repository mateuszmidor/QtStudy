#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "quickview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QuickView view;
    view.show();
    view.resize(800, 600);

    return app.exec();
}

