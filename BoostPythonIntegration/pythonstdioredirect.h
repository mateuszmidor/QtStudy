#ifndef PYTHONSTDIOREDIRECT
#define PYTHONSTDIOREDIRECT

#include <string>
#include <sstream>

class PythonStdIoRedirect {
public:

    void write(std::string const& str) {
        output << str;
    }

    std::string getOutput()
    {
        return output.str();
    }

    void clean()
    {
        output.str("");
    }

private:
     static std::stringstream output; // must be static, otherwise output is missing
};


#endif // PYTHONSTDIOREDIRECT

