#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QDebug>

#include "commands/command.hpp"

size_t MainWindow::model_count = 0;
size_t MainWindow::camera_count = 0;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->set_up_scene_view();
    this->set_up_model_view();
    this->update_scene_view();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
    ssize_t current_index = ui->modelChoiceButton->currentIndex() - 1;

    if (e->key() == Qt::Key_W) {
        commands::rotate_model_OX comm(-ANGLE, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_A) {
        commands::rotate_model_OY comm(ANGLE, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_S) {
        commands::rotate_model_OX comm(ANGLE, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_D) {
        commands::rotate_model_OY comm(-ANGLE, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_Z) {
        commands::rotate_model_OZ comm(ANGLE, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_X) {
        commands::rotate_model_OZ comm(-ANGLE, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_I) {
        point3d<double> point(0, - OFFSET, 0);
        commands::move comm(point, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_J) {
        point3d<double> point(-OFFSET, 0, 0);
        commands::move comm(point, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_K) {
        point3d<double> point(0, OFFSET, 0);
        commands::move comm(point, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_L) {
        point3d<double> point(OFFSET, 0, 0);
        commands::move comm(point, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_Plus) {
        commands::scale comm(SCALE_FACTOR, current_index);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_Plus) {
        commands::scale comm(1 / SCALE_FACTOR, current_index);
        this->command_controller.execute_command(comm);
    }

    this->update_scene_view();
}

void MainWindow::set_up_scene_view() {
    this->scene_view_scene = new QGraphicsScene(ui->sceneView);
    ui->sceneView->setMinimumSize(600, 600);
    ui->sceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->sceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->sceneView->installEventFilter(this);
}

void MainWindow::set_up_model_view() {
    this->model_view_scene = new QGraphicsScene(ui->modelView);
    ui->modelView->setMinimumSize(300, 300);
    ui->modelView->setMaximumSize(500, 500);
    ui->modelView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->modelView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::update_scene_view() {
    this->scene_view_scene->clear();
    commands::draw comm(this->scene_view_scene);
    this->command_controller.execute_command(comm);
    ui->sceneView->setScene(this->scene_view_scene);
}

void MainWindow::on_actionupload_model_triggered() {
    QString file_path = QFileDialog::getOpenFileName(this, QObject::tr("Specify file with model"),
                                                     QDir::currentPath(), QObject::tr("json (*.json)"));
    commands::upload_view comm(file_path.toStdString());
    this->command_controller.execute_command(comm);
    ui->listWidget->addItem(file_path.section("/", -1, -1).section(".", 0, 0));
}

void MainWindow::on_addSceneObjectButton_clicked() {
    if (ui->modelButton->isChecked()) {
        commands::add_model c3(ui->listWidget->currentIndex().column());
        this->command_controller.execute_command(c3);
        ui->modelChoiceButton->addItem(QString::number(MainWindow::model_count++) + " : model");
    }

    this->update_scene_view();
}

void MainWindow::on_removeSceneObjectButton_clicked() {

}

void MainWindow::on_deleteViewButton_clicked() {

}
