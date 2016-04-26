#ifndef OPENGLITEM
#define OPENGLITEM

#include <QQuickWindow>
#include <QQuickFramebufferObject>
#include "fborenderer.h"


// This is our OpenGl custom-rendered item; to be imported into QML (and so used on GUI thread)
class OpenGlItem : public QQuickFramebufferObject {
    Q_OBJECT
    float azimuth;

    Q_PROPERTY(float azimuth READ getAzimuth WRITE setAzimuth NOTIFY azimuthChanged)
public:
    // Constructor
    OpenGlItem(QQuickItem *parent = nullptr) : QQuickFramebufferObject(parent) { }

    // Inherited
    Renderer *createRenderer() const override {
        return new FBORenderer();
    }

    float getAzimuth() {
        return azimuth;
    }

    void setAzimuth(float value) {
        if (azimuth != value) {
            azimuth = value;
            emit azimuthChanged();
            update();
        }
    }

signals:
    void azimuthChanged();

};

#endif // OPENGLITEM

