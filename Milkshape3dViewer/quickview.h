#ifndef QUICKVIEW_H
#define QUICKVIEW_H

#include <QQuickView>
#include <QTimer>
#include "renderer.h"
#include "camera.h"

class QuickView : public QQuickView
{
    Q_OBJECT
    Camera camera;
    Renderer renderer;
    QTimer timer;
    const float TARGET_FPS = 60.0f;
    const float TARGET_DELTA_TIME_SEC = 1.f / TARGET_FPS;
public:
    QuickView(QWindow *parent = nullptr);
    void showCentralized();

signals:

public slots:
    void initializeUnderlay();
    void synchronizeUnderlay();
    void renderUnderlay();
    void invalidateUnderlay();
    void onTimer();
};

#endif // QUICKVIEW_H
