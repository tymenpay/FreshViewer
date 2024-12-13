#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include "3DModel.h"

#include <QOpenGLShaderProgram> 

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    void setModel(Model *model);
    void zoomCamera(float factor);
    void rotateCamera(float angle, float x, float y, float z);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void stop_paint() { abc = false; };
    void run_paint() {abc = true;};

    float cameraPosX = 0.0f;
    float cameraPosY = 0.0f;
    float cameraPosZ = 3.0f;
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    Model *model = nullptr;
    QOpenGLShaderProgram *shaderProgram = nullptr;
    bool abc = false;
    QPoint lastMousePosition;
};


#endif // OPENGLWIDGET_H
