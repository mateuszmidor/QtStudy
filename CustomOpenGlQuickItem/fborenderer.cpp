#include "fborenderer.h"
#include "openglitem.h"


FBORenderer::FBORenderer() {
    renderer.initialize();
}

QOpenGLFramebufferObject *FBORenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::Depth);
    return new QOpenGLFramebufferObject(size, format);
}

void FBORenderer::synchronize(QQuickFramebufferObject *item) {
    window = item->window();

    // Copy state to renderer
    OpenGlItem* i = static_cast<OpenGlItem *>(item);
    renderer.setAzimuth(i->getAzimuth());
    renderer.setViewportSize(QSize(item->width(), item->height()));
}

void FBORenderer::render() {
    renderer.render();
    window->resetOpenGLState();
}
