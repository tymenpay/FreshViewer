#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include <QHBoxLayout>
#include "OpenGLWidget.h"
#include "3DModel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void rotate();
    void move();
    void scale();

private:
    enum TransformationType {
        Move,
        Rotate,
        Scale
    };

    void setupUI();
    QHBoxLayout* createTransformLayout(const QString &label, QLineEdit* &xLine, QLineEdit* &yLine, QLineEdit* &zLine,
                                       QPushButton* &xPlus, QPushButton* &xMinus,
                                       QPushButton* &yPlus, QPushButton* &yMinus,
                                       QPushButton* &zPlus, QPushButton* &zMinus, QPushButton* &actionButton);
    void createConnections();
    void createTransformConnections(QLineEdit *xLine, QLineEdit *yLine, QLineEdit *zLine,
                                    QPushButton *xPlus, QPushButton *xMinus,
                                    QPushButton *yPlus, QPushButton *yMinus,
                                    QPushButton *zPlus, QPushButton *zMinus,
                                    QPushButton *actionButton,
                                    void (MainWindow::*actionFunc)());
    void adjustValue(QLineEdit *lineEdit, float delta);
    void resetTransformLines();
    void toggleControls(bool enabled);
    void applyTransformation(TransformationType type);

    OpenGLWidget *glWidget;
    Model *model;

    QPushButton *loadButton;
    QLineEdit *moveXLineEdit, *moveYLineEdit, *moveZLineEdit;
    QLineEdit *rotateXLineEdit, *rotateYLineEdit, *rotateZLineEdit;
    QLineEdit *scaleXLineEdit, *scaleYLineEdit, *scaleZLineEdit;

    QPushButton *moveXButton_plus, *moveXButton_minus;
    QPushButton *moveYButton_plus, *moveYButton_minus;
    QPushButton *moveZButton_plus, *moveZButton_minus;

    QPushButton *rotateXButton_plus, *rotateXButton_minus;
    QPushButton *rotateYButton_plus, *rotateYButton_minus;
    QPushButton *rotateZButton_plus, *rotateZButton_minus;

    QPushButton *scaleXButton_plus, *scaleXButton_minus;
    QPushButton *scaleYButton_plus, *scaleYButton_minus;
    QPushButton *scaleZButton_plus, *scaleZButton_minus;

    QPushButton *moveButton, *rotateButton, *scaleButton;
};

#endif // MAINWINDOW_H
