#ifndef CONSOLE
#define CONSOLE

#include <QString>
#include <iostream>
#include <string>

// convenience class for fetching user input from console
class Console {
public:
    static QString getUserInput() {
        std::string s;
        do {
            getline(std::cin, s);
        } while (s.empty()); // only accept non-epmty input

        return s.c_str();
    }
};

#endif // CONSOLE

