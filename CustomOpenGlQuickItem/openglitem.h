#ifndef OPENGLITEM
#define OPENGLITEM

#include <QQuickWindow>
#include <QQuickItem>
#include "openglrenderer.h"


// This is our OpenGl custom-rendered item; to be imported into QML (and so used on GUI thread)
class OpenGlItem : public QQuickItem {
    Q_OBJECT

    // the actual OpenGl content renderer
    OpenGlRenderer* renderer;

public:
    // Constructor
    OpenGlItem() : renderer(nullptr) {
        // handle the "QQuickItem::windowChanged" signal in "handleWindowChanged" slot
        connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
    }


public slots:
    // Synchronization stage. Its safe to copy the state from GUI thread to the Renderer thread here
    void syncRendererStateWithGuiState() {

        // in case this is the first pass, or the window has been invalidated -
        // create the renderer and make it handle the "QQuickWindow::beforeRendering" signal
        if (!renderer) {
            renderer = new OpenGlRenderer();

            // handle the actual rendering in OpenGlRenderer::render() slot
            connect(window(), SIGNAL(beforeRendering()), renderer, SLOT(render()), Qt::DirectConnection);
        }

        // tell the OpenGl renderer what is the current window size
        renderer->setViewportSize(window()->size() * window()->devicePixelRatio());

        // copy any additional state variables to the renderer here
        // ...
    }

    // Free the renderer resources
    void releaseRenderer()
    {
        if (renderer) {
            delete renderer;
            renderer = nullptr;
        }
    }

private slots:
    // Handle the new window assign/current window release action
    void handleWindowChanged(QQuickWindow *window)
    {
        // a new window is being assigned to our QuickItem. Have to configure it
        if (window) {
            // "QuickWindow::beforeSynchronizing"
            // during synchronisation we copy the state needed for rendering.
            // from QuickItem (GUI thread) into Renderer (Rendering thread)
            connect(window, SIGNAL(beforeSynchronizing()), this, SLOT(syncRendererStateWithGuiState()), Qt::DirectConnection);

            // "QQuickWindow::sceneGraphInvalidated"
            // sceneGraphInvalidated means all the scene graph resources are to be released (eg. window has been minimized)
            connect(window, SIGNAL(sceneGraphInvalidated()), this, SLOT(releaseRenderer()), Qt::DirectConnection);

            // tell the window not to clear the contents that we have just rendered into it :)
            window->setClearBeforeRendering(false);
        }
    }

};

/*
    To repaint the scene eg. to make smooth animation, use:
    if (window())
        window()->update();
*/

#endif // OPENGLITEM

