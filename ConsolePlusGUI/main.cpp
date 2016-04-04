#include <iostream>
#include "console.h"
#include "gui.h"

using namespace std;

int main(int argc, char *argv[])
{
    // a console, it runs as a dedicated QThread
    Console console;

    // gui, it runs on the main thread
    Gui gui;

    // make inter-thread connection from console to gui
    //, make sure the signal is handled on main (gui) thread -> QueuedConnection
    QObject::connect(&console, &Console::command, &gui, &Gui::onCommand, Qt::QueuedConnection);

    // run console thread
    console.start();

    // run the gui on main thread
    return gui.exec(argc, argv);
}
