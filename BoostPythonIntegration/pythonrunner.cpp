#include "pythonrunner.h"

using namespace std;
using namespace boost::python;

PythonRunner::PythonRunner() {
    initializePython();
}

void PythonRunner::initializePython() {
    // initialize the interpreter and main context
    Py_Initialize();
    object main_module = import("__main__");
    mainNamespace = main_module.attr("__dict__");

    // redirect python output to pythonOutputWriter
    mainNamespace["PythonStdIoRedirect"] = class_<PythonStdIoRedirect>("PythonStdIoRedirect", init<>())
        .def("write", &PythonStdIoRedirect::write);
    boost::python::import("sys").attr("stderr") = pythonOutputWriter;
    boost::python::import("sys").attr("stdout") = pythonOutputWriter;
}

std::string PythonRunner::run(const std::string& pythonCode) {
    // clean the output buffer
    pythonOutputWriter.clean();

    try {
        // run the python code, output goes through pythonOutputWriter
        object ignored = exec(pythonCode.c_str(), mainNamespace);

    } catch (error_already_set&) {
        // print error to stderr
        PyErr_Print();
    }

    // return python output
    return pythonOutputWriter.getOutput();
}
