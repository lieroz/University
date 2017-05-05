#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->currentFloorLCD->setStyleSheet("background : black;");
    ui->currentFloorLCD->setPalette(Qt::green);
    ui->currentFloorLCD->display(this->current_floor);
    ui->stateViewer->setText("undefined wait");

    this->setFixedSize(this->geometry().width(), this->geometry().height());

    this->set_up_call_button_signals();
    this->set_up_manage_button_signals();
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop_lift_button_clicked()));

    this->declare_states();
    this->set_up_transitions();
    this->set_up_machine();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::create_state(QState*& state, QString property, int duration, QState* parent) {
    state = new QState(parent);
    QTimer* timer = new QTimer(state);
    timer->setInterval(duration);
    timer->setSingleShot(true);
    QState* timing = new QState(state);
    connect(timing, SIGNAL(entered()), timer, SLOT(start()));
    QFinalState* done = new QFinalState(state);
    timing->addTransition(timer, SIGNAL(timeout()), done);
    state->setInitialState(timing);
    state->assignProperty(ui->stateViewer, "text", property);
}

void MainWindow::set_up_call_button_signals() {
    for (size_t i = 0; i < FLOOR_COUNT; ++i) {
        QString text = QString::number(i + 1);
        QPushButton* button = new QPushButton(text, this);
        this->call_buttons.push_back(button);
        ui->verticalLayout->addWidget(button);
        connect(this->call_buttons.at(i), SIGNAL(clicked()), this, SLOT(call_lift_button_clicked()));
    }
}

void MainWindow::set_up_manage_button_signals() {
    for (size_t i = 0; i < FLOOR_COUNT; ++i) {
        QString text = QString::number(i + 1);
        QPushButton* button = new QPushButton(text, this);
        this->manage_buttons.push_back(button);
        ui->verticalLayout_2->addWidget(button);
        connect(this->manage_buttons.at(i), SIGNAL(clicked()), this, SLOT(manage_lift_button_clicked()));
    }
}

void MainWindow::declare_states() {
    this->s1 = new QState();
    this->create_state(this->move, "move", 1000, this->s1);
    this->create_state(this->stop, "stop", 1000, this->s1);

    this->s2 = new QState();
    this->create_state(this->open, "open", 1000, this->s2);
    this->create_state(this->wait, "wait", 1000, this->s2);
    this->create_state(this->close, "close", 1000, this->s2);

    this->undefined_wait = new QFinalState();
}

void MainWindow::set_up_transitions() {
    this->s1->setInitialState(this->move);
    this->move->addTransition(this->move, SIGNAL(finished()), this->stop);
    this->stop->addTransition(this->stop, SIGNAL(finished()), this->s2);

    this->s2->setInitialState(this->open);
    this->open->addTransition(this->open, SIGNAL(finished()), this->wait);
    this->wait->addTransition(this->wait, SIGNAL(finished()), this->close);
    connect(this->close, SIGNAL(entered()), this, SLOT(check_slot()));
    this->close->addTransition(this, SIGNAL(queue_empty()), this->undefined_wait);
    this->close->addTransition(this, SIGNAL(queue_filled()), this->s1);
}

void MainWindow::set_up_machine() {
    this->machine.addState(this->s1);
    this->machine.addState(this->s2);
    this->machine.addState(this->undefined_wait);
}

void MainWindow::call_lift_button_clicked() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    const int button_number = button->text()[0].digitValue();
    this->machine.start();

    if (!this->machine.isRunning()) {

        if (button_number == this->current_floor) {
            emit call_button_clicked(button_number);
        }

        emit call_button_clicked(button_number);

    } else {
        this->queued_signals.push_back(button_number);
    }
}

void MainWindow::manage_lift_button_clicked() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    const int button_number = button->text()[0].digitValue();

    if (!this->machine.isRunning()) {
        this->machine.setInitialState(this->current_floor == button_number ? this->s2 : this->s1);
        this->machine.start();
//        emit manage_button_clicked(button_number);

    } else {
        this->queued_signals.push_back(button_number);
    }
}

void MainWindow::stop_lift_button_clicked() {

}

void MainWindow::check_slot() {
    if (queued_signals.empty()) {
        emit queue_empty();

    } else {
        emit queue_filled();
    }
}
