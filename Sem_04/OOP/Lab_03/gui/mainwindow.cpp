#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QDebug>

#include "commands/command.hpp"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->frame->setFixedWidth(250);
    this->set_up_scene_view();
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
    if (ui->modelButton->isChecked() && ui->listWidget->count() > 0) {
        commands::add_model comm(ui->listWidget->currentIndex().column());
        this->command_controller.execute_command(comm);
        ui->modelChoiceButton->addItem(QString::number(ui->modelChoiceButton->count() - 1) + " : model");
    }

    this->update_scene_view();
}

void MainWindow::on_removeSceneObjectButton_clicked() {
    if (ui->modelButton->isChecked() && ui->modelChoiceButton->currentIndex() > 0) {
        commands::remove_model comm(ui->modelChoiceButton->currentIndex() - 1);
        this->command_controller.execute_command(comm);
        size_t i = static_cast<size_t>(ui->modelChoiceButton->currentIndex());
        ui->modelChoiceButton->removeItem(ui->modelChoiceButton->currentIndex());

        for (; i < static_cast<size_t>(ui->modelChoiceButton->count()); ++i) {
            ui->modelChoiceButton->setItemText(i, QString::number(i - 1) + " : model");
        }
    }

    this->update_scene_view();
}

void MainWindow::on_deleteViewButton_clicked() {
    delete ui->listWidget->item(ui->listWidget->currentIndex().column());
}
