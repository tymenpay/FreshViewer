#include "OpenGLWidget.h"
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), model(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWidget::paintGL() {
    if (!abc) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -cameraPosZ);

    glRotatef(rotationX, 0.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);


    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    for (const auto& vertex : model->modelData->vertices) {
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    for (const auto& face : model->modelData->faces) {
        std::vector<int> faceVertices = face.vertexIndices;
        for (size_t i = 0; i < faceVertices.size(); ++i) {
            int vi1 = faceVertices[i];
            int vi2 = faceVertices[(i + 1) % faceVertices.size()];

            glVertex3f(model->modelData->vertices[vi1].x, model->modelData->vertices[vi1].y, model->modelData->vertices[vi1].z);
            glVertex3f(model->modelData->vertices[vi2].x, model->modelData->vertices[vi2].y, model->modelData->vertices[vi2].z);
        }
    }
    glEnd();
    glDisableClientState(GL_VERTEX_ARRAY);
    if (!model->modelData->normals.empty()) {
        glDisableClientState(GL_NORMAL_ARRAY);
    }
    if (!model->modelData->textureCoords.empty()) {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

}


void OpenGLWidget::setModel(Model *newModel) {
    abc = true;
    model = newModel;
    update();
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;
    glFrustum(-aspect, aspect, -1.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

}

void OpenGLWidget::zoomCamera(float factor) {
    cameraPosZ *= factor;
    update();
}

void OpenGLWidget::rotateCamera(float angle, float x, float y, float z) {
    rotationX += (x * angle);
    rotationY += (y * angle);
    rotationZ += (z * angle);
    update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event) {
    lastMousePosition = event->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
    QPoint delta = event->pos() - lastMousePosition;

    rotateCamera(delta.y() * 0.3f, 1.0f, 0.0f, 0.0f);
    rotateCamera(delta.x() * 0.3f, 0.0f, 1.0f, 0.0f);

    lastMousePosition = event->pos();
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
            zoomCamera(0.9f);
        } else if (event->key() == Qt::Key_Minus) {
            zoomCamera(1.1f);
        }
    }
}


