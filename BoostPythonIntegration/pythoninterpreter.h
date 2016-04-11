#ifndef PYTHONINTERPRETER
#define PYTHONINTERPRETER

#include <boost/python.hpp>
#include <QObject>

#include <iostream>

#include "pythonstdioredirect.h"

class PythonInterpreter : public QObject {
    Q_OBJECT

    // properties are visible from QML code
    Q_PROPERTY(QString output READ getOutput NOTIFY outputChanged)

public:
    PythonInterpreter() {
         // initialize python interpreter and execution context
         initializePython();

         // handle "run" signal in "runPythonCode" method
         QObject::connect(this, &PythonInterpreter::run, this, &PythonInterpreter::runPythonCode);
    }

    // "channelName" property getter
    QString getOutput() const {
        return output;
    }

    // "output" property setter
    void setOutput(const QString& newOutput) {
        if (output != newOutput) {
            output = newOutput;
            emit outputChanged();
        }
    }

signals:
    // "output" property changed signal - to be handled in QML code
    void outputChanged();

    // "run" gui event - to be fired from QML code
    void run(const QString &pythonCode);

private:
    QString output;
    boost::python::object main_namespace;
    PythonStdIoRedirect python_stdio_redirector;

private:
    void initializePython()
    {
        // initialize the interpreter and main context
        using namespace boost::python;
        Py_Initialize();
        object main_module = import("__main__");
        main_namespace = main_module.attr("__dict__");

        // redirect python output to PythonStdIoRedirect
        main_namespace["PythonStdIoRedirect"] = class_<PythonStdIoRedirect>("PythonStdIoRedirect", init<>())
            .def("write", &PythonStdIoRedirect::write);

        //boost::python::import("sys").attr("stderr") = python_stdio_redirector;
        boost::python::import("sys").attr("stdout") = python_stdio_redirector;
    }

    void runPythonCode(const QString &pythonCode) {
        using namespace boost::python;

        // clean the python output buffer
        python_stdio_redirector.clean();

        try {
            // run the python code
            object ignored = exec(pythonCode.toStdString().c_str(), main_namespace);

            // update the output to the python output
            setOutput(python_stdio_redirector.getOutput().c_str());
        } catch (error_already_set&) {
            PyErr_Print();
        }
    }
};

#endif // PYTHONINTERPRETER

