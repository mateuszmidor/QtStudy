#ifndef OPENGLRENDERER
#define OPENGLRENDERER

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QUrl>

// This is our OpenGl renderer; to be used on Renderer thread
class OpenGlRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    // Constructor
    OpenGlRenderer() :  shaderProgram(nullptr) { }

    // Destructor
    ~OpenGlRenderer() {
        // delete the shader program
        delete shaderProgram;
    }

    // Set new viewport size
    void setViewportSize(const QSize &size) {
        viewportSize = size;
    }

public slots:
    // The actual OpenGl rendering happens here
    void render() {

        if (!shaderProgram) {
            initializeOpenGLFunctions();

            shaderProgram = new QOpenGLShaderProgram();
            shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertexshader.glsl");
            shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragmentshader.glsl");

            shaderProgram->bindAttributeLocation("vertices", 0);
            shaderProgram->link();

        }
    //! [4] //! [5]
        shaderProgram->bind();

        shaderProgram->enableAttributeArray(0);

        float values[] = {
            -1, -1,
            1, -1,
            1, 1,
            -1, 1
        };
        // assign actual data to "vertices" attribute
        shaderProgram->setAttributeArray(0, GL_FLOAT, values, 2);
        //m_program->setUniformValue("t", (float) m_t);

        glViewport(0, 0, viewportSize.width(), viewportSize.height());

        glDisable(GL_DEPTH_TEST);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glDrawArrays(GL_QUADS, 0, 4);

        shaderProgram->disableAttributeArray(0);
        shaderProgram->release();

    }

private:
    QSize viewportSize;
    QOpenGLShaderProgram *shaderProgram;
};

#endif // OPENGLRENDERER

