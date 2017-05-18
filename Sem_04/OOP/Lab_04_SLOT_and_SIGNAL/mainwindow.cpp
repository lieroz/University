#include "mainwindow.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow()) {
    ui->setupUi(this);
    ui->lcdNumber->setStyleSheet("background : black;");
    ui->lcdNumber->setPalette(Qt::green);
    ui->lcdNumber->display(1);
    this->setUpCallButtons();
    this->setUpControlButtons();
    this->setUpConnections();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpCallButtons() {
    for (int i = 0; i < FLOOR_COUNT; ++i) {
        QString text = QString::number(i + 1);
        QPushButton* button = new QPushButton(text, this);
        this->callButtons.push_back(button);
        ui->verticalLayout->addWidget(button);
        connect(this->callButtons.at(i), SIGNAL(clicked()), this, SLOT(callButtonPressedSlot()));
    }
}

void MainWindow::setUpControlButtons() {
    for (int i = 0; i < FLOOR_COUNT; ++i) {
        QString text = QString::number(i + 1);
        QPushButton* button = new QPushButton(text, this);
        this->controlButtons.push_back(button);
        ui->verticalLayout_2->addWidget(button);
        connect(this->controlButtons.at(i), SIGNAL(clicked()), this, SLOT(controlButtonPressedSlot()));
    }
}

void MainWindow::setUpConnections() {
    connect(this, SIGNAL(callButtonPressedSignal(int)), &this->controller, SLOT(callButtonPressed(int)));
    connect(this, SIGNAL(controlButtonPressedSignal(int)), &this->controller, SLOT(controlButtonPressed(int)));
    connect(ui->stopButton, SIGNAL(clicked()), &this->controller, SLOT(stopButtonPressed()));
    connect(&this->controller, SIGNAL(setFloor(int)), this, SLOT(setFloor(int)));
    connect(&this->controller, SIGNAL(elevatorStateChanged(Elevator::State)), this, SLOT(elevatorStateAcceptor(Elevator::State)));
    connect(&this->controller, SIGNAL(doorsStateChanged(Doors::State)), this, SLOT(doorsStateAcceptor(Doors::State)));
}

void MainWindow::callButtonPressedSlot() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    const int buttonNumber = button->text()[0].digitValue();
    emit callButtonPressedSignal(buttonNumber);
}

void MainWindow::controlButtonPressedSlot() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    const int buttonNumber = button->text()[0].digitValue();
    emit controlButtonPressedSignal(buttonNumber);
}

void MainWindow::setFloor(int value) {
    ui->lcdNumber->display(value);
}

void MainWindow::elevatorStateAcceptor(Elevator::State state) {
    switch (state) {
        case Elevator::State::MOVING:
            ui->statusBar->showMessage("ELEVATOR MOVING");
            break;

        case Elevator::State::FLOOR_CHANGED:
            ui->statusBar->showMessage("ELEVATOR FLOOR CHANGED");
            break;

        case Elevator::State::STOPPED:
            ui->statusBar->showMessage("ELEVATOR STOPPED");
            break;

        case Elevator::State::WAITING:
            ui->statusBar->showMessage("ELEVATOR WAITING");
            break;

        case Elevator::State::UNDEFINED_WAITING:
            ui->statusBar->showMessage("ELEVATOR UNDEFINED WAITING");
            break;

        default:
            break;
    }
}

void MainWindow::doorsStateAcceptor(Doors::State state) {
    switch (state) {
        case Doors::State::OPENING:
            ui->statusBar->showMessage("DOORS OPENING");
            break;

        case Doors::State::OPENED:
            ui->statusBar->showMessage("DOORS OPENED");
            break;

        case Doors::State::CLOSING:
            ui->statusBar->showMessage("DOORS CLOSING");
            break;

        case Doors::State::CLOSED:
            ui->statusBar->showMessage("DOORS CLOSED");
            break;

        default:
            break;
    }
}
