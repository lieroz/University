#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->frame->setFixedWidth(this->FRAME_SIZE);
    ui->graphicsView->setMinimumSize(this->width() - this->FRAME_SIZE, this->height());
    ui->graphicsView->setMouseTracking(true);
    ui->lineColorButton->setStyleSheet("background-color: rgb(0, 0, 0)");
    this->scene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    this->pixmap = new QPixmap(ui->graphicsView->width(), ui->graphicsView->height());
    this->pixmap->fill(Qt::white);
    this->setUpSpinBorders();
    this->setMinimumSize(QSize(1110, 680));
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->scene;
    delete this->pixmap;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    ui->graphicsView->resize(event->size().width() - this->FRAME_SIZE - 22, event->size().height() - 18);
    delete this->scene;
    this->scene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    delete this->pixmap;
    this->pixmap = new QPixmap(ui->graphicsView->width(), ui->graphicsView->height());
    this->pixmap->fill(Qt::white);

    if (ui->tabWidget->currentIndex() == 0) {

        for (const auto& item : this->scene_lines) {
            this->drawLine(item.__algorithm, item.__line, item.__color);
        }
    }

    else if (ui->tabWidget->currentIndex() == 1) {

        for (const auto& item : this->scene_stars) {
            this->drawStar(item.__algorithm, item.__line, item.__color);
        }
    }

    ui->graphicsView->setScene(this->scene);
    this->setUpSpinBorders();
}

void MainWindow::setUpSpinBorders() {
    ui->xSpin1->setMaximum(ui->graphicsView->width());
    ui->ySpin1->setMaximum(ui->graphicsView->height());
    ui->xSpin2->setMaximum(ui->graphicsView->width());
    ui->ySpin2->setMaximum(ui->graphicsView->height());

    ui->xSpinCenter->setMaximum(ui->graphicsView->width());
    ui->ySpinCenter->setMaximum(ui->graphicsView->height());
    ui->angleSpin->setMaximum(360);
    ui->widthSpin->setMaximum(ui->graphicsView->width() / 2);
}

void MainWindow::drawLine(Algorithms::algorithm algorithm, QLineF line, QColor color) {
    switch (algorithm) {
        case Algorithms::algorithm::STANDARD: {
            Algorithms::standard(this->scene, this->pixmap, line, color);
            break;
        }

        case Algorithms::algorithm::CDA: {
            Algorithms::cda(this->scene, this->pixmap, line, color);
            break;
        }

        case Algorithms::algorithm::BREZENHAM_INT: {
            Algorithms::brezenham_int(this->scene, this->pixmap, line, color);
            break;
        }

        case Algorithms::algorithm::BREZENHAM_DOUBLE: {
            Algorithms::brezenham_double(this->scene, this->pixmap, line, color);
            break;
        }

        case Algorithms::algorithm::BREZENHAM_GRADATION: {
            Algorithms::brezenham_gradation(this->scene, this->pixmap, line, color);
            break;
        }
    }
}

void MainWindow::drawStar(Algorithms::algorithm algorithm, QLineF line, QColor color) {
    const double length = ui->widthSpin->value();
    const double angle = ui->angleSpin->value() * M_PI / 180;
    QLineF buf_line = line;

    for (double i = 0; i < 2 * M_PI; i += angle) {
        buf_line.setPoints(buf_line.p1(), QPointF(length * cos(i) + buf_line.p1().x(), length * sin(i) + buf_line.p1().y()));
        this->drawLine(algorithm, buf_line, color);
    }
}

void MainWindow::measureTime(Timer& timer, QString& data, QLineF& line,
                             std::function<void(Algorithms::algorithm, QLineF, QColor)>& func) {
    timer.reset();
    func(Algorithms::algorithm::STANDARD, line, Qt::white);
    data += QString("Standard: " + QString::number(timer.elapsed()) + " ns\n");

    timer.reset();
    func(Algorithms::algorithm::CDA, line, Qt::white);
    data += QString("DDA: " + QString::number(timer.elapsed()) + " ns\n");

    timer.reset();
    func(Algorithms::algorithm::BREZENHAM_INT, line, Qt::white);
    data += QString("Brezenham integer: " + QString::number(timer.elapsed()) + " ns\n");

    timer.reset();
    func(Algorithms::algorithm::BREZENHAM_DOUBLE, line, Qt::white);
    data += QString("Brezenham double: " + QString::number(timer.elapsed()) + " ns\n");

    timer.reset();
    func(Algorithms::algorithm::BREZENHAM_GRADATION, line, Qt::white);
    data += QString("Brezenham gradation: " + QString::number(timer.elapsed()) + " ns\n");
}

void MainWindow::on_lineColorButton_clicked() {
    this->line_color = QColorDialog::getColor();
    ui->lineColorButton->setStyleSheet("background-color: rgb(" +
                                       QString::number(line_color.red()) + "," +
                                       QString::number(line_color.green()) + "," +
                                       QString::number(line_color.blue()) + ")");
}

void MainWindow::on_drawButton_clicked() {
    Algorithms::algorithm algorithm = static_cast<Algorithms::algorithm>(ui->algorithmsComboBox->currentIndex());

    if (ui->tabWidget->currentIndex() == 0) {
        QLineF line = QLineF(ui->xSpin1->value(), ui->ySpin1->value(), ui->xSpin2->value(), ui->ySpin2->value());
        this->drawLine(algorithm, line, this->line_color);
        this->scene_lines.push_back(LineWrapper(line, this->line_color, algorithm));
    }

    else if (ui->tabWidget->currentIndex() == 1) {
        QLineF line = QLineF(ui->xSpinCenter->value(), ui->ySpinCenter->value(), ui->widthSpin->value(),
                             ui->ySpinCenter->value());
        this->drawStar(algorithm, line, this->line_color);
        this->scene_stars.push_back(LineWrapper(line, this->line_color, algorithm));
    }

    ui->graphicsView->setScene(this->scene);
}

void MainWindow::on_timeButton_clicked() {
    Timer timer;
    QString data;

    if (ui->tabWidget->currentIndex() == 0) {
        QLineF line = QLineF(ui->xSpin1->value(), ui->ySpin1->value(), ui->xSpin2->value(), ui->ySpin2->value());
        std::function<void(Algorithms::algorithm, QLineF, QColor)> func =
            std::bind(&MainWindow::drawLine, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        this->measureTime(timer, data, line, func);
    }

    else if (ui->tabWidget->currentIndex() == 1) {
        QLineF line = QLineF(ui->xSpinCenter->value(), ui->ySpinCenter->value(), ui->widthSpin->value(),
                             ui->ySpinCenter->value());
        std::function<void(Algorithms::algorithm, QLineF, QColor)> func =
            std::bind(&MainWindow::drawStar, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        this->measureTime(timer, data, line, func);
    }

    QMessageBox::information(this, QObject::tr("Algorthms time"), QObject::tr(data.toStdString().c_str()));
}

void MainWindow::on_cleanButton_clicked() {
    this->scene_lines.clear();
    this->scene_stars.clear();
    this->scene->clear();
    this->pixmap->fill(Qt::white);
}
