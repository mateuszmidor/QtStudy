#ifndef PYTHONINTERPRETER
#define PYTHONINTERPRETER

#include <QObject>
#include <boost/python.hpp>
#include <iostream>

class PythonInterpreter : public QObject {
    Q_OBJECT

    // properties are visible from QML code
    Q_PROPERTY(QString output READ getOutput NOTIFY outputChanged)

public:
    PythonInterpreter() {
         QObject::connect(this, &PythonInterpreter::run, this, &PythonInterpreter::runPythonCode);
         Py_Initialize();
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
    QString output = "[Python output is currently being sent to termianal]";
    void runPythonCode(const QString &pythonCode) {
        using namespace boost::python;
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");

        try {
                object ignored = exec(pythonCode.toStdString().c_str(), main_namespace);
                std::cout << std::flush;
                //setOutput(ss.str().c_str());
            } catch (error_already_set&) {
                PyErr_Print();
            }        
    }
};

#endif // PYTHONINTERPRETER

