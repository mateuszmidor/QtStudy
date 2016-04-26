#ifndef RENDERER
#define RENDERER

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "cMS3DModel.h"

class Renderer : public QObject, protected QOpenGLFunctions  {
    Q_OBJECT

    float azimuth, elevation, distance;
    QSize viewportSize;
    QOpenGLShaderProgram *shaderProgram;
    QMatrix4x4 projectionMatrix;
    QString modelFilename;
    CMS3DModel model;

public:
    // Constructor
    Renderer() : shaderProgram(nullptr) {}

    // Destructor
    virtual ~Renderer() {
        // delete the shader program
        delete shaderProgram;
    }

    void setAzimuth(float value) {
        azimuth = value;
    }

    void setElevation(float value) {
        elevation = value;
    }

    void setDistance(float value) {
        distance = value;
    }

    void setModelFilename(const QString &filename) {
        if (modelFilename != filename) {
            modelFilename = filename;
            model.Load(filename.toStdString().c_str());
        }
    }

    // Set new viewport size
    void setViewportSize(const QSize &size) {
        viewportSize = size;
        projectionMatrix.setToIdentity();
        projectionMatrix.perspective(45.0, (float)viewportSize.width() / viewportSize.height(), 1.0, 1000.0);
        glViewport(0, 0, viewportSize.width(), viewportSize.height());
    }

    // Init the renderer
    void initialize() {
        if (!shaderProgram) {
            initializeOpenGLFunctions();

            shaderProgram = new QOpenGLShaderProgram();
            shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/data/shader.vert");
            shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/data/shader.frag");

            shaderProgram->bindAttributeLocation("vertices", 0);
            shaderProgram->link();
        }

       // model.Load("data/Diablo.ms3d");
    }

    void invalidate() {
    }

    // Prepare next animation frame
    void prepare(float deltaTime) {
        model.Prepare(deltaTime);
    }

    // Render the scene
    void render() {
        QMatrix4x4 modelviewMatrix;
        modelviewMatrix.translate(0.0, -32, distance);
        modelviewMatrix.rotate(elevation, 1.0, 0.0, 0.0);
        modelviewMatrix.rotate(azimuth, 0.0, 1.0, 0.0);

        shaderProgram->bind();
        shaderProgram->setUniformValue("mv_matrix", modelviewMatrix);
        shaderProgram->setUniformValue("p_matrix", projectionMatrix);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.5, 0.5, 1.0, 1);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model.Draw();

        shaderProgram->release();
    }
};

#endif // RENDERER

