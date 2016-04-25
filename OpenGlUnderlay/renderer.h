#ifndef RENDERER
#define RENDERER

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class Renderer : protected QOpenGLFunctions {
    float azimuth, elevation, distance;
    QSize viewportSize;
    QOpenGLShaderProgram *shaderProgram;
    QMatrix4x4 projection;

    // Return an array of vertices that make up triangles that make up our cube
    const float* getCubeVertices() {
        static const float TRIANGLE_VERTICES[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        };
        return TRIANGLE_VERTICES;
    }

public:
    // Constructor
    Renderer() : azimuth(45.0f), elevation(15.0f), distance(-6.0f), shaderProgram(nullptr) {}

    // Destructor
    ~Renderer() {
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

    // Set new viewport size
    void setViewportSize(const QSize &size) {
        viewportSize = size;
        projection.setToIdentity();
        projection.perspective(45.0, (float)viewportSize.width() / viewportSize.height(), 1.0, 100.0);
        glViewport(0, 0, viewportSize.width(), viewportSize.height());
    }

    // Init the renderer
    void initialize() {
        if (!shaderProgram) {
            initializeOpenGLFunctions();

            shaderProgram = new QOpenGLShaderProgram();
            shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
            shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");

            shaderProgram->bindAttributeLocation("vertices", 0);
            shaderProgram->link();
        }
    }

    void invalidate() {
    }

    // Render the scene
    void render() {
        shaderProgram->bind();
        shaderProgram->enableAttributeArray(0);

        // assign actual data to "vertices" attribute
        shaderProgram->setAttributeArray(0, GL_FLOAT, getCubeVertices(), 3);

        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, distance);
        matrix.rotate(elevation, 1.0, 0.0, 0.0);
        matrix.rotate(azimuth, 0.0, 1.0, 0.0);

        shaderProgram->setUniformValue("mvp_matrix", projection * matrix);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 1);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 12*3);

        shaderProgram->disableAttributeArray(0);
        shaderProgram->release();
    }
};

#endif // RENDERER

