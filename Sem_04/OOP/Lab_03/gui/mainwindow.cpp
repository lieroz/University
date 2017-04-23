#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

#include "commands/command.hpp"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->set_up_scene_view();
    this->set_up_model_view();
    commands::upload_view c1("/home/lieroz/University/Sem_04/OOP/Lab_03/DATA/cube.json");
    this->command_controller.execute_command(c1);
    commands::add_model c3(0);
    this->command_controller.execute_command(c3);
    this->update_scene_view();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_W) {
        commands::rotate_model_OX comm(-ANGLE, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_A) {
        commands::rotate_model_OY comm(ANGLE, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_S) {
        commands::rotate_model_OX comm(ANGLE, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_D) {
        commands::rotate_model_OY comm(-ANGLE, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_Z) {
        commands::rotate_model_OZ comm(ANGLE, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_X) {
        commands::rotate_model_OZ comm(-ANGLE, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_I) {
        point3d<double> point(0, - OFFSET, 0);
        commands::move comm(point, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_J) {
        point3d<double> point(-OFFSET, 0, 0);
        commands::move comm(point, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_K) {
        point3d<double> point(0, OFFSET, 0);
        commands::move comm(point, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_L) {
        point3d<double> point(OFFSET, 0, 0);
        commands::move comm(point, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_Plus) {
        commands::scale comm(SCALE_FACTOR, -1);
        this->command_controller.execute_command(comm);

    } else if (e->key() == Qt::Key_Plus) {
        commands::scale comm(1 / SCALE_FACTOR, -1);
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
