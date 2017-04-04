#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, ui{new Ui::MainWindow} {
    ui->setupUi(this);
    this->setFixedSize(QSize{this->WINDOW_WIDTH, this->WINDOW_HEIGHT});
    this->setUpView();
    this->scene = new QGraphicsScene{0, 0, static_cast<double>(ui->graphicsView->width()), static_cast<double>(ui->graphicsView->height())};
    this->setUpScene();
    this->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpText() {
    QGraphicsTextItem* text1 = this->scene->addText("0, 340");
    text1->setPos(0, 340);
    QGraphicsTextItem* text2 = this->scene->addText("340, 0");
    text2->setPos(340, 0);
    QGraphicsTextItem* text3 = this->scene->addText("680, 340");
    text3->setPos(615, 340);
    QGraphicsTextItem* text4 = this->scene->addText("340, 680");
    text4->setPos(340, 655);
}

void MainWindow::setUpView() {
    ui->graphicsView->setFixedSize(QSize{ui->graphicsView->width(), ui->graphicsView->height()});
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->installEventFilter(this);
}

void MainWindow::setUpLines() {
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
}

void MainWindow::setUpScene() {
    this->angle = 0;
    this->x_offset_point = 0;
    this->y_offset_point = 0;
    this->x_scale_coef = 1;
    this->y_scale_coef = 1;
    this->x_scale_point = this->x_rotation_point = static_cast<double>(ui->graphicsView->width()) / 2;
    this->y_scale_point = this->y_rotation_point = static_cast<double>(ui->graphicsView->height()) / 2;

    for (qreal t{}; t < 2 * M_PI; t += STEP) {
        Point2D point = Point2D{this->x_rotation_point + this->SIDE * pow(cos(t), 3), this->y_rotation_point + this->SIDE * pow(sin(t), 3)};
        this->points.append(point);
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    this->setUpLines();
    this->setUpText();
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

void MainWindow::setUpScaling(double x_coef, double y_coef) {
    for (auto& point : this->points) {
        point.x = x_coef * point.x + this->x_scale_point * (1 - x_coef);
        point.y = y_coef * point.y + this->y_scale_point * (1 - y_coef);
    }
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

void MainWindow::on_scaleButton_clicked() {
    if (std::regex_match(ui->xScaleCoefLineEdit->text().toStdString(), this->is_number) &&
        std::regex_match(ui->yScaleCoefLineEdit->text().toStdString(), this->is_number) &&
        std::regex_match(ui->xScaleLineEdit->text().toStdString(), this->is_number) &&
        std::regex_match(ui->yScaleLineEdit->text().toStdString(), this->is_number)) {
        this->x_scale_coef = ui->xScaleCoefLineEdit->text().toDouble();
        this->y_scale_coef = ui->yScaleCoefLineEdit->text().toDouble();
        this->x_scale_point = ui->xScaleLineEdit->text().toDouble();
        this->x_scale_point = ui->yScaleLineEdit->text().toDouble();

    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный тип данных!");
    }

    this->setUpScaling(this->x_scale_coef, this->y_scale_coef);
    this->scene->clear();

    for (auto& point : this->points) {
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    this->setUpText();
    this->setUpLines();
}

void MainWindow::on_rotateButton_clicked() {
    if (std::regex_match(ui->xRotLineEdit->text().toStdString(), this->is_number) &&
        std::regex_match(ui->yRotLineEdit->text().toStdString(), this->is_number) &&
        std::regex_match(ui->angleLineEdit->text().toStdString(), this->is_number)) {
        this->x_rotation_point = ui->xRotLineEdit->text().toDouble();
        this->y_rotation_point = ui->yRotLineEdit->text().toDouble();
        this->angle = ui->angleLineEdit->text().toDouble();

    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный тип данных!");
    }

    this->setUpRotation(this->angle);
    this->scene->clear();

    for (auto& point : this->points) {
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    this->setUpText();
    this->setUpLines();
}

void MainWindow::on_offsetButton_clicked() {
    if (std::regex_match(ui->xMoveLineEdit->text().toStdString(), this->is_number) &&
        std::regex_match(ui->yMoveLineEdit->text().toStdString(), this->is_number)) {
        this->x_offset_point = ui->xMoveLineEdit->text().toDouble();
        this->y_offset_point = ui->yMoveLineEdit->text().toDouble();

    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный тип данных!");
    }

    for (auto& point : this->points) {
        point.x += this->x_offset_point;
        point.y += this->y_offset_point;
    }

    this->scene->clear();

    for (auto& point : this->points) {
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    this->setUpText();
    this->setUpLines();
}

void MainWindow::on_resetButton_clicked() {
    ui->xMoveLineEdit->clear();
    ui->yMoveLineEdit->clear();
    ui->angleLineEdit->clear();
    ui->xRotLineEdit->clear();
    ui->yRotLineEdit->clear();
    ui->xScaleCoefLineEdit->clear();
    ui->yScaleCoefLineEdit->clear();
    ui->xScaleLineEdit->clear();
    ui->yScaleLineEdit->clear();
    this->scene->clear();
    this->points.clear();
    this->setFocus();
    this->setUpScene();
}

void MainWindow::on_undoScaleButton_clicked() {
    this->setUpScaling(1.0 / this->x_scale_coef, 1.0 / this->y_scale_coef);
    this->scene->clear();

    for (auto& point : this->points) {
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    this->setUpText();
    this->setUpLines();
}

void MainWindow::on_undoOffsetButton_clicked() {
    for (auto& point : this->points) {
        point.x -= this->x_offset_point;
        point.y -= this->y_offset_point;
    }

    this->scene->clear();

    for (auto& point : this->points) {
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    this->setUpText();
    this->setUpLines();
}

void MainWindow::on_undoRotateButton_clicked() {
    this->setUpRotation(-(this->angle));
    this->scene->clear();

    for (auto& point : this->points) {
        this->scene->addEllipse(point.x - this->RADIUS, point.y - this->RADIUS,
                                this->RADIUS * 2, this->RADIUS * 2, QPen{Qt::black}, QBrush{Qt::black});
    }

    this->setUpText();
    this->setUpLines();
}
