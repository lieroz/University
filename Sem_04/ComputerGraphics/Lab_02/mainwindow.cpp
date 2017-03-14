#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, ui{new Ui::MainWindow} {
    ui->setupUi(this);
    this->setFixedSize(QSize{this->WINDOW_WIDTH, this->WINDOW_HEIGHT});
    this->setUpView();
    this->setUpScene();
    this->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpView() {
    ui->graphicsView->setFixedSize(QSize{ui->graphicsView->width(), ui->graphicsView->height()});
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->installEventFilter(this);
}

void MainWindow::setUpScene() {
    this->scene = new QGraphicsScene{0, 0, static_cast<qreal>(ui->graphicsView->width()), static_cast<qreal>(ui->graphicsView->height())};
    const double x_center = this->x_scale_point = this->x_rotation_point = static_cast<double>
                                                                           (ui->graphicsView->width()) / 2;
    const double y_center = this->y_scale_point = this->y_rotation_point = static_cast<double>
                                                                           (ui->graphicsView->height()) / 2;

    for (qreal t{}; t < 2 * M_PI; t += STEP) {
        Point2D point = Point2D{x_center + this->SIDE * pow(cos(t), 3), y_center + this->SIDE * pow(sin(t), 3)};
        this->points.append(point);
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    QPen pen = QPen{Qt::black};
    pen.setWidth(5);

    this->scene->addLine(this->points[0].x, this->points[0].y,
                         this->points[this->points.size() / 4].x, this->points[this->points.size() / 4].y, pen);
    this->scene->addLine(this->points[this->points.size() / 4].x, this->points[this->points.size() / 4].y,
                         this->points[this->points.size() / 2].x, this->points[this->points.size() / 2].y, pen);
    this->scene->addLine(this->points[this->points.size() / 2].x, this->points[this->points.size() / 2].y,
                         this->points[3 * this->points.size() / 4].x, this->points[3 * this->points.size() / 4].y, pen);
    this->scene->addLine(this->points[3 * this->points.size() / 4].x, this->points[3 * this->points.size() / 4].y,
                         this->points[0].x, this->points[0].y, pen);

    ui->graphicsView->setScene(this->scene);
}

void MainWindow::setUpRotation(double angle) {
    angle *= M_PI / 180.0;

    for (auto& point : this->points) {
        const double x_point = point.x;
        const double y_point = point.y;
        point.x = (x_point - this->x_rotation_point) * cos(angle) - (y_point - this->y_rotation_point) * sin(
                      angle) + this->x_rotation_point;
        point.y = (x_point - this->x_rotation_point) * sin(angle) + (y_point - this->y_rotation_point) * cos(
                      angle) + this->y_rotation_point;
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {

        case Qt::Key_A: {
            setUpRotation(this->angle);
            break;
        }

        case Qt::Key_D: {
            setUpRotation(-(this->angle));
            break;
        }

        case Qt::Key_Up: {
            for (auto& point : this->points) {
                point.y -= 5;
            }

            break;
        }

        case Qt::Key_Down: {
            for (auto& point : this->points) {
                point.y += 5;
            }

            break;
        }

        case Qt::Key_Left: {
            for (auto& point : this->points) {
                point.x -= 5;
            }

            break;
        }

        case Qt::Key_Right: {
            for (auto& point : this->points) {
                point.x += 5;
            }

            break;
        }

        case Qt::Key_Plus: {
            ui->graphicsView->scale(1.5, 1.5);
            break;
        }

        case Qt::Key_Minus: {
            ui->graphicsView->scale(0.5, 0.5);
        }

        default:
            return;
    }

    this->scene->clear();

    for (auto& point : this->points) {
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    QPen pen = QPen{Qt::black};
    pen.setWidth(5);

    this->scene->addLine(this->points[0].x, this->points[0].y,
                         this->points[this->points.size() / 4].x, this->points[this->points.size() / 4].y, pen);
    this->scene->addLine(this->points[this->points.size() / 4].x, this->points[this->points.size() / 4].y,
                         this->points[this->points.size() / 2].x, this->points[this->points.size() / 2].y, pen);
    this->scene->addLine(this->points[this->points.size() / 2].x, this->points[this->points.size() / 2].y,
                         this->points[3 * this->points.size() / 4].x, this->points[3 * this->points.size() / 4].y, pen);
    this->scene->addLine(this->points[3 * this->points.size() / 4].x, this->points[3 * this->points.size() / 4].y,
                         this->points[0].x, this->points[0].y, pen);

    this->setFocus();
}

void MainWindow::on_action_triggered() {
    QMessageBox::information(this, "Условие задачи",
                             QString{"Нарисовать исходную фигуру , затем ее \n"
                                     "переместить, промасштабировать и повернуть.\n\n"
                                     "\t+-------+\n"
                                     "\t|           |\n"
                                     "\t|           |\n"
                                     "\t+-------+\n\n"
                                     "Внутри находится астроида, ее уравнение {\n"
                                     "\t\tx = b(cos(t))^3,\n"
                                     "\t\ty = b(sin(t))^3,\n"
                                     "\t\tt in [0, 2pi]\n"
                                     "\t}"});
}
