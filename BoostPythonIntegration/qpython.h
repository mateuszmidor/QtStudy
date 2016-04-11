#ifndef PYTHONINTERPRETER
#define PYTHONINTERPRETER

#include <QObject>
#include "pythonrunner.h"

// QObject accessible from QML, can run python code and return output
class QPython : public QObject {
    Q_OBJECT

    // properties visible from QML code
    Q_PROPERTY(QString output READ getOutput NOTIFY outputChanged)

public:
    QPython() {
         // handle "run" signal in "runPythonCode" method
         QObject::connect(this, &QPython::run, this, &QPython::runPythonCode);
    }

    // "output" property getter
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

    // "run" event - to be fired from QML code
    void run(const QString &pythonCode);

private:
    QString output;
    PythonRunner pythonRuner;

private:
    // python code execution happens here
    void runPythonCode(const QString &pythonCode) {
        // run the code in python interprete
        std::string output = pythonRuner.run(pythonCode.toStdString());

        // update the output to the python output
        setOutput(output.c_str());
    }
};

#endif // PYTHONINTERPRETER
