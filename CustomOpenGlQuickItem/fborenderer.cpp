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
    renderer.setViewportSize(window->size());

    OpenGlItem* i = static_cast<OpenGlItem *>(item);
    renderer.setAzimuth(i->getAzimuth());
}

void FBORenderer::render() {
    renderer.render();
    window->resetOpenGLState();
}
