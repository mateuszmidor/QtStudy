#ifndef PYTHONRUNNER_H
#define PYTHONRUNNER_H

#include <boost/python.hpp>
#include <iostream>
#include "pythonstdioredirect.h"

class PythonRunner
{
    boost::python::object mainNamespace;
    PythonStdIoRedirect pythonOutputWriter;

    void initializePython();

public:
    // constructor; initialize python interpreter
    PythonRunner();

    // run python code and return stdout/stderr as string
    std::string run(const std::string& pythonCode);
};

#endif // PYTHONRUNNER_H
