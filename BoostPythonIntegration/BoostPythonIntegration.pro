TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

RESOURCES += qml.qrc

INCLUDEPATH += /usr/local/lib/boost/installation/include/
INCLUDEPATH += /usr/include/python2.7/

LIBS += -L/usr/local/lib/boost/installation/lib/ -lboost_python
LIBS += -lpython2.7

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    pythoninterpreter.h

