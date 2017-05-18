#include "mainwindow.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow()) {
    ui->setupUi(this);
    ui->lcdNumber->setStyleSheet("background : black;");
    ui->lcdNumber->setPalette(Qt::green);
    ui->lcdNumber->display(1);
    ui->elevator->setStyleSheet("background-color:gray;");
    this->setUpCallButtons();
    this->setUpControlButtons();
    this->setUpConnections();
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    this->elevatorAnimation = new QPropertyAnimation(ui->elevator, "geometry");
    this->leftDoorAnimation = new QPropertyAnimation(ui->leftDoor, "geometry");
    this->rightDoorAnimation = new QPropertyAnimation(ui->rightDoor, "geometry");
    this->leftDoorWidth = ui->leftDoor->width();
    this->rightDoorWidth = ui->rightDoor->width();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpCallButtons() {
    for (int i = 0; i < FLOOR_COUNT; ++i) {
        QString text = QString::number(FLOOR_COUNT - i);
        QPushButton* button = new QPushButton(text, this);
        button->setFixedSize(50, 50);
        this->callButtons.push_back(button);
        ui->verticalLayout->addWidget(button);
        connect(this->callButtons.at(i), SIGNAL(clicked()), this, SLOT(callButtonPressedSlot()));
    }
}

void MainWindow::setUpControlButtons() {
    for (int i = 0; i < FLOOR_COUNT; ++i) {
        QString text = QString::number(FLOOR_COUNT - i);
        QPushButton* button = new QPushButton(text, this);
        button->setFixedSize(50, 50);
        this->controlButtons.push_back(button);
        ui->verticalLayout_2->addWidget(button);
        connect(this->controlButtons.at(i), SIGNAL(clicked()), this, SLOT(controlButtonPressedSlot()));
    }
}

void MainWindow::setUpConnections() {
    connect(this, SIGNAL(callButtonPressedSignal(int)), &this->controller, SLOT(callButtonPressed(int)));
    connect(this, SIGNAL(controlButtonPressedSignal(int)), &this->controller, SLOT(controlButtonPressed(int)));
    connect(&this->controller, SIGNAL(setFloor(int)), this, SLOT(setFloor(int)));
    connect(&this->controller, SIGNAL(elevatorStateChanged(Elevator::State, bool)), this, SLOT(elevatorStateAcceptor(Elevator::State, bool)));
    connect(&this->controller, SIGNAL(doorsStateChanged(Doors::State)), this, SLOT(doorsStateAcceptor(Doors::State)));
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setPen(QColor("#d4d4d4"));
    this->increment = (this->window()->height() - 25) / FLOOR_COUNT;
    int y = 16;

    for (int i = 0; i < FLOOR_COUNT; ++i) {
        painter.drawLine(200, y, 535, y);
        y += this->increment;
    }
}

void MainWindow::updateElevator(bool movingUp) {
    this->elevatorAnimation->setDuration(TIMER_LARGE);
    this->elevatorAnimation->setEasingCurve(QEasingCurve::Linear);
    this->elevatorAnimation->setEndValue(QRect(ui->elevator->pos().x(),
                                               movingUp ? ui->elevator->pos().y() - this->increment : ui->elevator->pos().y() + this->increment,
                                               ui->elevator->width(), ui->elevator->height()));
    this->elevatorAnimation->start();
}

void MainWindow::updateDoorsOpening() {
    this->leftDoorAnimation->setDuration(TIMER_MID);
    this->rightDoorAnimation->setDuration(TIMER_MID);
    this->leftDoorAnimation->setEasingCurve(QEasingCurve::Linear);
    this->rightDoorAnimation->setEasingCurve(QEasingCurve::Linear);
    this->leftDoorAnimation->setEndValue(QRect(ui->leftDoor->pos().x(), ui->leftDoor->pos().y(),
                                               0, ui->leftDoor->height()));
    this->rightDoorAnimation->setEndValue(QRect(ui->rightDoor->pos().x() + ui->rightDoor->width(),
                                                ui->rightDoor->pos().y(), 0, ui->rightDoor->height()));
    this->leftDoorAnimation->start();
    this->rightDoorAnimation->start();
}

void MainWindow::updateDoorsClosing() {
    this->leftDoorAnimation->setDuration(TIMER_MID);
    this->rightDoorAnimation->setDuration(TIMER_MID);
    this->leftDoorAnimation->setEasingCurve(QEasingCurve::Linear);
    this->rightDoorAnimation->setEasingCurve(QEasingCurve::Linear);
    this->leftDoorAnimation->setEndValue(QRect(ui->leftDoor->pos().x(), ui->leftDoor->pos().y(),
                                               this->leftDoorWidth, ui->leftDoor->height()));
    this->rightDoorAnimation->setEndValue(QRect(ui->rightDoor->pos().x() - this->rightDoorWidth, ui->rightDoor->pos().y(),
                                                this->rightDoorWidth, ui->rightDoor->height()));
    this->leftDoorAnimation->start();
    this->rightDoorAnimation->start();
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

void MainWindow::elevatorStateAcceptor(Elevator::State state, bool movingUp) {
    switch (state) {
        case Elevator::State::MOVING:
            ui->statusBar->showMessage("ELEVATOR MOVING");
            this->updateElevator(movingUp);
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
            this->updateDoorsOpening();
            break;

        case Doors::State::OPENED:
            ui->statusBar->showMessage("DOORS OPENED");
            break;

        case Doors::State::CLOSING:
            ui->statusBar->showMessage("DOORS CLOSING");
            this->updateDoorsClosing();
            break;

        case Doors::State::CLOSED:
            ui->statusBar->showMessage("DOORS CLOSED");
            break;

        default:
            break;
    }
}
