#ifndef CONSOLE
#define CONSOLE

#include <QString>
#include <iostream>
#include <string>

class Console {

public:
    static QString getUserInput() {
        std::string s;
        do {
            getline(std::cin, s);
        } while (s.empty());

        return s.c_str();
    }
};

#endif // CONSOLE

