#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), model(new Model()) {
    setupUI();
    createConnections();
    toggleControls(false);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout;

    glWidget = new OpenGLWidget();
    layout->addWidget(glWidget);

    loadButton = new QPushButton("Open File", this);
    layout->addWidget(loadButton);

    layout->addLayout(createTransformLayout("Rotate", rotateXLineEdit, rotateYLineEdit, rotateZLineEdit,
                                           rotateXButton_plus, rotateXButton_minus,
                                           rotateYButton_plus, rotateYButton_minus,
                                           rotateZButton_plus, rotateZButton_minus, rotateButton));

    layout->addLayout(createTransformLayout("Move", moveXLineEdit, moveYLineEdit, moveZLineEdit,
                                           moveXButton_plus, moveXButton_minus,
                                           moveYButton_plus, moveYButton_minus,
                                           moveZButton_plus, moveZButton_minus, moveButton));

    layout->addLayout(createTransformLayout("Scale", scaleXLineEdit, scaleYLineEdit, scaleZLineEdit,
                                           scaleXButton_plus, scaleXButton_minus,
                                           scaleYButton_plus, scaleYButton_minus,
                                           scaleZButton_plus, scaleZButton_minus, scaleButton));

    centralWidget->setLayout(layout);
}

QHBoxLayout* MainWindow::createTransformLayout(const QString &label, QLineEdit* &xLine, QLineEdit* &yLine, QLineEdit* &zLine,
                                              QPushButton* &xPlus, QPushButton* &xMinus,
                                              QPushButton* &yPlus, QPushButton* &yMinus,
                                              QPushButton* &zPlus, QPushButton* &zMinus, QPushButton* &actionButton) {
    QHBoxLayout *layout = new QHBoxLayout;
    QLabel *labelX = new QLabel(label + " X", this);
    QLabel *labelY = new QLabel(label + " Y", this);
    QLabel *labelZ = new QLabel(label + " Z", this);

    xLine = new QLineEdit(this);
    yLine = new QLineEdit(this);
    zLine = new QLineEdit(this);

    xPlus = new QPushButton(">", this);
    xMinus = new QPushButton("<", this);
    yPlus = new QPushButton(">", this);
    yMinus = new QPushButton("<", this);
    zPlus = new QPushButton(">", this);
    zMinus = new QPushButton("<", this);
    actionButton = new QPushButton(label, this);

    layout->addWidget(labelX);
    layout->addWidget(xMinus);
    layout->addWidget(xLine);
    layout->addWidget(xPlus);

    layout->addWidget(labelY);
    layout->addWidget(yMinus);
    layout->addWidget(yLine);
    layout->addWidget(yPlus);

    layout->addWidget(labelZ);
    layout->addWidget(zMinus);
    layout->addWidget(zLine);
    layout->addWidget(zPlus);

    layout->addWidget(actionButton);

    return layout;
}

void MainWindow::createConnections() {
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::openFile);

    createTransformConnections(rotateXLineEdit, rotateYLineEdit, rotateZLineEdit,
                               rotateXButton_plus, rotateXButton_minus,
                               rotateYButton_plus, rotateYButton_minus,
                               rotateZButton_plus, rotateZButton_minus, rotateButton,
                               &MainWindow::rotate);

    createTransformConnections(moveXLineEdit, moveYLineEdit, moveZLineEdit,
                               moveXButton_plus, moveXButton_minus,
                               moveYButton_plus, moveYButton_minus,
                               moveZButton_plus, moveZButton_minus, moveButton,
                               &MainWindow::move);

    createTransformConnections(scaleXLineEdit, scaleYLineEdit, scaleZLineEdit,
                               scaleXButton_plus, scaleXButton_minus,
                               scaleYButton_plus, scaleYButton_minus,
                               scaleZButton_plus, scaleZButton_minus, scaleButton,
                               &MainWindow::scale);
}

void MainWindow::createTransformConnections(QLineEdit *xLine, QLineEdit *yLine, QLineEdit *zLine,
                                           QPushButton *xPlus, QPushButton *xMinus,
                                           QPushButton *yPlus, QPushButton *yMinus,
                                           QPushButton *zPlus, QPushButton *zMinus,
                                           QPushButton *actionButton, void (MainWindow::*actionFunc)()) {
    connect(xPlus, &QPushButton::clicked, this, [=] { adjustValue(xLine, 0.1f); });
    connect(xMinus, &QPushButton::clicked, this, [=] { adjustValue(xLine, -0.1f); });
    connect(yPlus, &QPushButton::clicked, this, [=] { adjustValue(yLine, 0.1f); });
    connect(yMinus, &QPushButton::clicked, this, [=] { adjustValue(yLine, -0.1f); });
    connect(zPlus, &QPushButton::clicked, this, [=] { adjustValue(zLine, 0.1f); });
    connect(zMinus, &QPushButton::clicked, this, [=] { adjustValue(zLine, -0.1f); });
    connect(actionButton, &QPushButton::clicked, this, actionFunc);
}

void MainWindow::adjustValue(QLineEdit *lineEdit, float delta) {
    float value = lineEdit->text().toFloat();
    lineEdit->setText(QString::number(value + delta));
}

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open OBJ File", "", "OBJ Files (*.obj);;All Files (*)");
    if (!filename.isEmpty() && model->parseObjFile(filename.toStdString())) {
        glWidget->setModel(model);
        glWidget->update();
        toggleControls(true);
        resetTransformLines();
    } else {
        qDebug() << "Failed to load the model.";
    }
}

void MainWindow::resetTransformLines() {
    for (QLineEdit *lineEdit : {moveXLineEdit, moveYLineEdit, moveZLineEdit,
                                rotateXLineEdit, rotateYLineEdit, rotateZLineEdit,
                                scaleXLineEdit, scaleYLineEdit, scaleZLineEdit}) {
        lineEdit->setText("0.0");
    }
}

void MainWindow::toggleControls(bool enabled) {
    for (QLineEdit *lineEdit : {moveXLineEdit, moveYLineEdit, moveZLineEdit,
                                rotateXLineEdit, rotateYLineEdit, rotateZLineEdit,
                                scaleXLineEdit, scaleYLineEdit, scaleZLineEdit}) {
        lineEdit->setEnabled(enabled);
    }
}
void MainWindow::applyTransformation(TransformationType type) {
    float valueX = 0.0f;
    float valueY = 0.0f;
    float valueZ = 0.0f;

    switch (type) {
        case Move:
            valueX = moveXLineEdit->text().toFloat();
        valueY = moveYLineEdit->text().toFloat();
        valueZ = moveZLineEdit->text().toFloat();
        break;
        case Rotate:
            valueX = rotateXLineEdit->text().toFloat();
        valueY = rotateYLineEdit->text().toFloat();
        valueZ = rotateZLineEdit->text().toFloat();
        break;
        case Scale:
            valueX = scaleXLineEdit->text().toFloat();
        valueY = scaleYLineEdit->text().toFloat();
        valueZ = scaleZLineEdit->text().toFloat();
        break;
    }

    glWidget->stop_paint();

    switch (type) {
        case Move:
            model->move_figure(valueX, valueY, valueZ);
        break;
        case Rotate:
            model->rotate_figure(valueX, valueY, valueZ);
        break;
        case Scale:
            model->scaling_figure(valueX, valueY, valueZ);
        break;
    }

    glWidget->setModel(model);
    glWidget->update();
}

void MainWindow::move() {
    applyTransformation(Move);
}

void MainWindow::rotate() {
    applyTransformation(Rotate);
}

void MainWindow::scale() {
    applyTransformation(Scale);
}