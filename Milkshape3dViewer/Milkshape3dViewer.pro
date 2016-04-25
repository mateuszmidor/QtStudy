TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    uMS3D_mathlib.cpp \
    quickview.cpp \
    cMS3DModel.cpp

LIBS +=  -lGLU

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    uMS3D_mathlib.h \
    camera.h \
    quickview.h \
    renderer.h \
    cMS3DModel.h

