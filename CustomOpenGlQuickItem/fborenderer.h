#ifndef FBORENDERER
#define FBORENDERER

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>
#include "cuberenderer.h"


class FBORenderer : public QQuickFramebufferObject::Renderer {
    QQuickWindow *window;
    CubeRenderer renderer;

public:
    FBORenderer();

    // Inherited
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    // Inherited
    void synchronize(QQuickFramebufferObject *item) override ;

    // Inherited
    void render() override;
};

#endif // FBORENDERER

