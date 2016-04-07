#include <iostream>
#include "tuner.h"
#include "gui.h"
#include "sdarsqobject.h"
using namespace std;

int main(int argc, char *argv[])
{
    // a tuner, it runs as a separate thread (QThread in this example)
    Tuner tuner;

    // our QObject to be exposed to GUI
    SdarsQObject qobject;

    // gui, it runs on the main thread and uses qobject to communicate with tuner both ways
    Gui gui(qobject);

    // tuner -> gui connection
    QObject::connect(&tuner, &Tuner::tunedToChannel, &qobject, &SdarsQObject::setChannelName);

    // gui -> tuner connection
    QObject::connect(&qobject, &SdarsQObject::nextChannelClicked, &tuner, &Tuner::nextChannel);

    // run tuner thread
    tuner.start();

    // run the gui on main thread, block until window is closed
    return gui.exec(argc, argv);
}
