#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, ui{new Ui::MainWindow} {
    ui->setupUi(this);
    this->setFixedSize(QSize{WINDOW_WIDTH, WINDOW_HEIGHT});
    this->setUpCanvas();
    this->setUpTables();
    this->setUpAnswerTables();
    this->scene = new QGraphicsScene{0, 0, static_cast<qreal>(ui->canvas->width()), static_cast<qreal>(ui->canvas->height())};
    this->scene->setParent(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpCanvas() {
    this->canvas_width = ui->canvas->width();
    this->canvas_height = ui->canvas->height();

    ui->canvas->setFixedSize(QSize{this->canvas_width, this->canvas_height});
    ui->canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->canvas->scale(SCALE_FACTOR, SCALE_FACTOR);
}

void MainWindow::setUpTables() {
    ui->leftTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->rightTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->leftTable->horizontalScrollBar()->setEnabled(false);
    ui->rightTable->horizontalScrollBar()->setEnabled(false);

    ui->leftTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->rightTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->leftTable->setColumnCount(COLUMN_COUNT);
    ui->rightTable->setColumnCount(COLUMN_COUNT);

    ui->leftTable->setHorizontalHeaderLabels(QStringList() << "X" << "Y");
    ui->rightTable->setHorizontalHeaderLabels(QStringList() << "X" << "Y");

    for (int i{}; i < 2; ++i) {
        ui->leftTable->setColumnWidth(i, ui->leftTable->width() / 2);
        ui->rightTable->setColumnWidth(i, ui->rightTable->width() / 2);
    }
}

void MainWindow::setUpAnswerTables() {
    ui->leftAnswerTable->setColumnCount(COLUMN_COUNT);
    ui->rightAnswerTable->setColumnCount(COLUMN_COUNT);
    ui->leftAnswerTable->setRowCount(ROW_COUNT);
    ui->rightAnswerTable->setRowCount(ROW_COUNT);

    ui->leftAnswerTable->setHorizontalHeaderLabels(QStringList() << "X" << "Y");
    ui->rightAnswerTable->setHorizontalHeaderLabels(QStringList() << "X" << "Y");

    for (int i{}; i < ROW_COUNT; ++i) {

        for (int j{}; j < COLUMN_COUNT; ++j) {
            QTableWidgetItem* left_item = new QTableWidgetItem{};
            ui->leftAnswerTable->setItem(i, j, left_item);
            ui->leftAnswerTable->item(i, j)->setFlags(ui->leftAnswerTable->item(i, j)->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem* right_item = new QTableWidgetItem{};
            ui->rightAnswerTable->setItem(i, j, right_item);
            ui->rightAnswerTable->item(i, j)->setFlags(ui->rightAnswerTable->item(i, j)->flags() ^ Qt::ItemIsEditable);
        }
    }

    for (int i{}; i < 2; ++i) {
        ui->leftAnswerTable->setColumnWidth(i, ui->leftAnswerTable->width() / 2 - 7);
        ui->rightAnswerTable->setColumnWidth(i, ui->rightAnswerTable->width() / 2 - 7);
    }
}

void MainWindow::on_action_triggered() {
    QMessageBox::information(this, "Условие задачи",
                             QString{"На плоскости даны два множества точек. "} +
                             QString{"Найти пару треугольников (каждый треугольник "} +
                             QString{"в качестве вершины имеет три различные точки "} +
                             QString{"одного и того же множества, пространства треугольников "} +
                             QString{"строятся на точках разных множеств), таких что прямая, соединяющая "} +
                             QString{"точки пересечения высот, образует минимальный угол с осью абсцисс. "} +
                             QString{"Сделать в графическом режиме вывод изображения."});
}

void MainWindow::on_leftAddButton_clicked() {
    ui->leftTable->insertRow(ui->leftTable->rowCount());
    ui->leftTable->verticalScrollBar()->setSliderPosition(ui->leftTable->verticalScrollBar()->maximum());
    ui->leftTable->setColumnWidth(0, ui->leftTable->width() / 2 - ui->leftTable->verticalHeader()->width());
    ui->leftTable->setColumnWidth(1, ui->leftTable->width() / 2 - ui->leftTable->verticalScrollBar()->width());
}

void MainWindow::on_leftDeleteButton_clicked() {
    if (ui->leftTable->rowCount() > 1) {
        ui->leftTable->removeRow(ui->leftTable->currentRow());
    }
}

void MainWindow::on_rightAddButton_clicked() {
    ui->rightTable->insertRow(ui->rightTable->rowCount());
    ui->rightTable->verticalScrollBar()->setSliderPosition(ui->rightTable->verticalScrollBar()->maximum());
    ui->rightTable->setColumnWidth(0, ui->rightTable->width() / 2 - ui->rightTable->verticalHeader()->width());
    ui->rightTable->setColumnWidth(1, ui->rightTable->width() / 2 - ui->rightTable->verticalScrollBar()->width());

}

void MainWindow::on_rightDeleteButton_clicked() {
    if (ui->rightTable->rowCount() > 1) {
        ui->rightTable->removeRow(ui->rightTable->currentRow());
    }
}

void MainWindow::fillVector(QVector<QPoint>& vector, QTableWidget* table) {
    for (int i{}; i < table->rowCount(); ++i) {

        if (table->item(i, 0) != nullptr && table->item(i, 1) != nullptr) {
            const int x = table->item(i, 0)->data(Qt::DisplayRole).toInt();
            const int y = table->item(i, 1)->data(Qt::DisplayRole).toInt();
            vector.append(QPoint{x, y});
        }
    }
}

void MainWindow::on_drawButton_clicked() {
    QVector<QPoint> first_set, second_set;
    MainWindow::fillVector(first_set, ui->leftTable);
    MainWindow::fillVector(second_set, ui->rightTable);

    this->scene->clear();

    DimensionSetter::setUpDimension(this->scene, first_set, second_set);
    Drawer::drawPoints(this->scene, first_set, second_set);

    ui->canvas->setScene(this->scene);
}

void MainWindow::on_solveButton_clicked() {
    QVector<QPoint> first_set, second_set;
    MainWindow::fillVector(first_set, ui->leftTable);
    MainWindow::fillVector(second_set, ui->rightTable);

    if (first_set.size() >= 3 && second_set.size() >= 3) {
        const QVector<QVector<QPoint>> vector = Solver::solve(first_set, second_set);
        const double angle = qRadiansToDegrees(qAtan(static_cast<double>(qAbs(vector[0].at(3).y() - vector[1].at(3).y()))
                                                     / static_cast<double>(qAbs(vector[0].at(3).x() - vector[1].at(3).x()))));
        QMessageBox::information(this, "Решение",
                                 "Минимальный угол с осью абсцисс: " + QString::number(angle));

    } else {
        QMessageBox::warning(this, "Ошибка",
                             "Невозможно решить задачу");
    }
}

void MainWindow::on_drawSolutionButton_clicked() {
    QVector<QPoint> first_set, second_set;
    MainWindow::fillVector(first_set, ui->leftTable);
    MainWindow::fillVector(second_set, ui->rightTable);

    if (first_set.size() >= 3 && second_set.size() >= 3) {
        this->scene->clear();

    } else {
        QMessageBox::warning(this, "Ошибка",
                             "Невозможно решить задачу");
        return;
    }

    QVector<QVector<QPoint>> vector = Solver::solve(first_set, second_set);
    first_set.append(vector[0].at(3));
    second_set.append(vector[1].at(3));
    DimensionSetter::setUpDimension(this->scene, first_set, second_set);

    auto iter = [](const QVector<QPoint>& points) {
        for (auto& point : points) {
            qDebug() << point;
        }
    };

    iter(vector[0]);
    iter(vector[1]);

    for (int i{}; i < ROW_COUNT; ++i) {
        ui->leftAnswerTable->item(i, 0)->setText(QString::number(vector[0].at(i).x()));
        ui->leftAnswerTable->item(i, 1)->setText(QString::number(vector[0].at(i).y()));
        ui->rightAnswerTable->item(i, 0)->setText(QString::number(vector[1].at(i).x()));
        ui->rightAnswerTable->item(i, 1)->setText(QString::number(vector[1].at(i).y()));
    }

    first_set.removeLast();
    second_set.removeLast();
    vector = Solver::solve(first_set, second_set);

    Drawer::drawAnswer(this->scene, vector[0], vector[1]);
    first_set.append(vector[0].at(3));
    second_set.append(vector[1].at(3));
    Drawer::drawPoints(this->scene, first_set, second_set);

    ui->canvas->setScene(this->scene);
}
