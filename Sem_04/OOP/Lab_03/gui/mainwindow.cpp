#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "canvasgl.hpp"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->sceneView->show();
    setFocusPolicy( Qt::StrongFocus );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
    ui->sceneView->keyPressEvent(e);
}
