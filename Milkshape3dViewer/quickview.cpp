#include <QQuickWindow>
#include <QScreen>
#include "quickview.h"


QuickView::QuickView(QWindow *parent) : QQuickView(parent), camera(new Camera()), renderer(new Renderer())
{
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(0);
    format.setSamples(8);
    setFormat(format);

    connect(this, &QQuickWindow::sceneGraphInitialized, this, &QuickView::initializeUnderlay, Qt::DirectConnection);
    connect(this, &QQuickWindow::beforeSynchronizing, this, &QuickView::synchronizeUnderlay, Qt::DirectConnection);
    connect(this, &QQuickWindow::beforeRendering, this, &QuickView::renderUnderlay, Qt::DirectConnection);
    connect(this, &QQuickWindow::sceneGraphInvalidated, this, &QuickView::invalidateUnderlay, Qt::DirectConnection);

    // connect (camera, &Camera::azimuthChanged, this, &QQuickWindow::update); // force emitting QQuickWindow::beforeSynchronizing

    setClearBeforeRendering(false);
    setPersistentOpenGLContext(true);

    setResizeMode(SizeRootObjectToView);
   // rootContext()->setContextProperty("_camera", camera);
    setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QuickView::onTimer);
    timer->start(16);
}

void QuickView::showCentralized() {
    unsigned x = (screen()->size().width() - size().width()) / 2;
    unsigned y = (screen()->size().height() - size().height()) / 2;
    setPosition(x, y);
    QQuickView::show();
}

// On timer event; every 16ms
void QuickView::onTimer() {
    const float dt = 16.0f / 1000;
    camera->azimuth += 15.f * dt;
    update();
}

void QuickView::initializeUnderlay() {
    renderer->initialize();
    resetOpenGLState();
}

void QuickView::synchronizeUnderlay() {
    renderer->setAzimuth(camera->azimuth);
    renderer->setElevation(camera->elevation);
    renderer->setDistance(camera->distance);
    renderer->setViewportSize(this->size());
}

void QuickView::renderUnderlay() {

    renderer->render();
    resetOpenGLState();
}

void QuickView::invalidateUnderlay() {

    renderer->invalidate();
    resetOpenGLState();
}
