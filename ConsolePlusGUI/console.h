#ifndef CONSOLE
#define CONSOLE

#include <QThread>
#include <iostream>
using namespace std;

// Console, it runs on separate thread so the main thread can handle GUI
class Console: public QThread {

    Q_OBJECT

    // thread main function
    void run() Q_DECL_OVERRIDE {

        // simply loop forever asking the user for input and emitting it in a signal
        while (true) {
            string s;
            cout << "Say: ";
            getline(cin, s);
            cout << ">" << s << endl;
            emit command(s.c_str());
        }
    }

signals:
    void command(const QString &s);
};

#endif // CONSOLE

