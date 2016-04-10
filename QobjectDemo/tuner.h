#ifndef TUNER
#define TUNER

#include <QThread>
#include <iostream>
#include "somechannels.h"
#include "console.h"

using namespace std;

// Tuner, it runs on separate thread so the main thread can handle GUI
class Tuner: public QThread {

    Q_OBJECT

    // a bunch of channels we can choose from
    SomeChannels channels;
private:

    // thread main function
    void run() Q_DECL_OVERRIDE {

        // simply loop forever, asking the user for input and emitting it in "tunedToChannel" signal
        while (true) {
            cout << "[tune to] > ";
            QString s = Console::getUserInput();
            emit tunedToChannel(s);
        }
    }

// interface for interacting with QObject
signals:
    // send signals to qobject
    void tunedToChannel(const QString &channelName);

public slots:
    // receive signals from qobject
    void nextChannel() {
        cout << "\n[tuner] next channel" << endl;
        emit tunedToChannel(channels.nextChannel());
    }
};

#endif // TUNER

