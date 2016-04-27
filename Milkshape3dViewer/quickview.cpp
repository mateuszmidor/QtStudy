#include <QQuickWindow>
#include <QQmlContext>
#include <QScreen>
#include "quickview.h"


QuickView::QuickView(QWindow *parent) : QQuickView(parent)
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
    rootContext()->setContextProperty("_rendererControl", &rendererControl);
    rootContext()->setContextProperty("_cameraControl", &camera);

    setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    connect(&timer, &QTimer::timeout, this, &QuickView::onTimer);
    timer.start(TARGET_DELTA_TIME_SEC * 1000);
}

void QuickView::showCentralized() {
    unsigned x = (screen()->size().width() - size().width()) / 2;
    unsigned y = (screen()->size().height() - size().height()) / 2;
    setPosition(x, y);
    QQuickView::show();
}

// On timer event; every 16ms
void QuickView::onTimer() {
    camera.azimuth += 15.f * TARGET_DELTA_TIME_SEC;
    update();
}

// [Render thread]
void QuickView::initializeUnderlay() {
    renderer.initialize();
    resetOpenGLState();
}

// [Render thread]
void QuickView::synchronizeUnderlay() {
    renderer.setAzimuth(camera.azimuth);
    renderer.setElevation(camera.elevation);
    renderer.setDistance(camera.getDistance());
    renderer.setViewportSize(this->size());
    renderer.setModelFilename(rendererControl.getModelFilename());
    renderer.prepare(TARGET_DELTA_TIME_SEC);
}

// [Render thread]
void QuickView::renderUnderlay() {
    renderer.render();
    resetOpenGLState();
}

// [Render thread]
void QuickView::invalidateUnderlay() {

    renderer.invalidate();
    resetOpenGLState();
}
