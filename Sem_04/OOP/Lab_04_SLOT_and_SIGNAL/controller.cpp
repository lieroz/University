#include "controller.hpp"
#include <QDebug>
#include <QApplication>

Controller::Controller(QObject* parent) : QObject(parent) {
    this->setUpConnections();
}

void Controller::setUpConnections() {
    connect(this, SIGNAL(move()), &this->elevator, SLOT(enteredMoving()));
    connect(&this->elevator, SIGNAL(finishedMoving()), this, SLOT(finishedMoving()));
    connect(this, SIGNAL(changeFloor()), &this->elevator, SLOT(enteredFloorChanged()));
    connect(&this->elevator, SIGNAL(finishedFloorChanged()), this, SLOT(finishedFloorChanged()));
    connect(this, SIGNAL(stop()), &this->elevator, SLOT(enteredStopped()));
    connect(&this->elevator, SIGNAL(finishedStopped()), this, SLOT(finishedStopped()));
    connect(this, SIGNAL(open()), &this->doors, SLOT(enteredOpening()));
    connect(&this->doors, SIGNAL(finishedOpened()), &this->elevator, SLOT(enteredWaiting()));
    connect(&this->elevator, SIGNAL(finishedWaiting()), &this->doors, SLOT(enteredClosing()));
    connect(&this->doors, SIGNAL(finishedClosed()), this, SLOT(finishedClosed()));
    connect(this, SIGNAL(shutDown()), &this->elevator, SLOT(shuttedDown()));
    connect(&this->elevator, SIGNAL(stateChanged(Elevator::State)), this, SLOT(elevatorStateChangedAcceptor(Elevator::State)));
    connect(&this->doors, SIGNAL(stateChanged(Doors::State)), this, SLOT(doorsStateChangedAcceptor(Doors::State)));
}

void Controller::callButtonPressed(int value) {
    this->blockSignals(false);

    if (this->elevator.getState() == Elevator::State::UNDEFINED_WAITING
        && this->doors.getState() == Doors::State::CLOSED) {

        if (value == this->currentFloor) {
            emit open();

        } else {
            this->destinationFloor = value;
            emit move();
        }

    } else {
        this->callSignals.enqueue(value);
    }
}

void Controller::controlButtonPressed(int value) {
    this->blockSignals(false);

    if (this->elevator.getState() == Elevator::State::UNDEFINED_WAITING
        && this->doors.getState() == Doors::State::CLOSED) {

        if (value == this->currentFloor) {
            emit open();

        } else {
            this->destinationFloor = value;
            emit move();
        }

    } else {
        this->controlSignals.enqueue(value);
    }
}

void Controller::stopButtonPressed() {
    this->callSignals.clear();
    this->controlSignals.clear();
    emit shutDown();
    this->blockSignals(true);
}

void Controller::finishedMoving() {
    emit changeFloor();
}

void Controller::finishedFloorChanged() {
    this->currentFloor > this->destinationFloor ? --this->currentFloor : ++this->currentFloor;
    emit setFloor(this->currentFloor);

    if (this->currentFloor == this->destinationFloor) {
        emit stop();

    } else {
        emit move();
    }
}

void Controller::finishedStopped() {
    emit open();
}

void Controller::finishedClosed() {
    if (callSignals.isEmpty() && controlSignals.isEmpty()) {
        emit shutDown();

    } else {

        if (this->callSignals.isEmpty() && !this->controlSignals.isEmpty()) {
            this->destinationFloor = this->controlSignals.dequeue();

        } else if (!this->callSignals.isEmpty() && this->controlSignals.isEmpty()) {
            this->destinationFloor = this->callSignals.dequeue();

        } else {

            if (this->callSignals.first() < this->controlSignals.first()) {
                this->destinationFloor = this->callSignals.dequeue();

            } else {
                this->destinationFloor = this->controlSignals.dequeue();
            }
        }

        if (this->currentFloor == this->destinationFloor) {
            emit open();

        } else {
            emit move();
        }
    }
}

void Controller::elevatorStateChangedAcceptor(Elevator::State state) {
    emit elevatorStateChanged(state);
}

void Controller::doorsStateChangedAcceptor(Doors::State state) {
    emit doorsStateChanged(state);
}
