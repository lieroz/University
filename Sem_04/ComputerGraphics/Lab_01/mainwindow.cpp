#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, ui{new Ui::MainWindow} {
    ui->setupUi(this);
    this->setFixedSize(QSize{WINDOW_WIDTH, WINDOW_HEIGHT});
    this->setUpCanvas();
    this->setUpTables();
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
    scene->clear();
    QVector<QPoint> first_set, second_set;
    MainWindow::fillVector(first_set, ui->leftTable);
    MainWindow::fillVector(second_set, ui->rightTable);

    DimensionSetter::setUpDimension(this->scene, first_set, second_set);

    for (auto& point : first_set) {
        qDebug() << point;
    }

    Drawer::drawSetPoints(scene, first_set);
    ui->canvas->setScene(scene);
}

void MainWindow::on_solveButton_clicked() {

}
