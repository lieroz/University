#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->setUpStateMachine();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::create_state(QState*& state, const char* name, int slot_id, int duration, QState* parent) {
    state = new QState(parent);
    QTimer* timer = new QTimer(state);
    timer->setInterval(duration);
    timer->setSingleShot(true);
    QState* timing = new QState(state);

    switch (slot_id) {
        case 0:
            connect(timing, SIGNAL(entered()), this, SLOT(wait_slot()));
            break;

        case 1:
            connect(timing, SIGNAL(entered()), this, SLOT(move_slot()));
            break;

        case 2:
            connect(timing, SIGNAL(entered()), this, SLOT(stop_slot()));
            break;

        case 3:
            connect(timing, SIGNAL(entered()), this, SLOT(open_doors_slot()));
            break;

        case 4:
            connect(timing, SIGNAL(entered()), this, SLOT(close_doors_slot()));
            break;

        default:
            throw std::logic_error("No slot for such name");
    }

    connect(timing, SIGNAL(entered()), timer, SLOT(start()));
    QFinalState* done = new QFinalState(state);
    timing->addTransition(timer, SIGNAL(timeout()), done);
    state->setInitialState(timing);
    state->setObjectName(name);
}

void MainWindow::setUpStateMachine() {
    create_state(this->wait, "Wait State", 0, 1000);
    create_state(this->move, "Move State", 1, 1000);
    this->wait->addTransition(this->wait, SIGNAL(finished()), this->move);
    create_state(this->stop, "Stop State", 2, 1000);
    this->move->addTransition(this->move, SIGNAL(finished()), this->stop);
    create_state(this->open_doors, "Open Doors State", 3, 1000);
    this->stop->addTransition(this->stop, SIGNAL(finished()), this->open_doors);
    create_state(this->close_doors, "Close Doors State", 4, 1000);
    this->open_doors->addTransition(this->open_doors, SIGNAL(finished()), this->close_doors);
    this->close_doors->addTransition(this->close_doors, SIGNAL(finished()), this->wait);

    this->state_machine.addState(this->wait);
    this->state_machine.addState(this->move);
    this->state_machine.addState(this->stop);
    this->state_machine.addState(this->open_doors);
    this->state_machine.addState(this->close_doors);
    this->state_machine.setInitialState(this->wait);
}

void MainWindow::wait_slot() {
    qDebug() << "wait slot";
}

void MainWindow::move_slot() {
    qDebug() << "move slot";
}

void MainWindow::stop_slot() {
    qDebug() << "stop slot";
}

void MainWindow::open_doors_slot() {
    qDebug() << "open doors slot";
}

void MainWindow::close_doors_slot() {
        this->state_machine.stop();
    qDebug() << "close doors slot";
}

void MainWindow::on_pushButton_clicked() {
        this->state_machine.start();
}
