TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

RESOURCES += qml.qrc

INCLUDEPATH += /usr/local/lib/boost/installation/include/
INCLUDEPATH += /usr/include/python2.7/

LIBS += /usr/local/lib/boost/installation/lib/libboost_python.so
LIBS += /usr/lib/x86_64-linux-gnu/libpython2.7.so

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

