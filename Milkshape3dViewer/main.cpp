#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "quickview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QuickView view;
    view.resize(640, 480);
    view.showCentralized();

    return app.exec();
}

