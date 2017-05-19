#include "elevator.hpp"
#include <QDebug>

Elevator::Elevator(QObject* parent) : QObject(parent) {
    this->setUpTimers();
    this->setUpConnections();
}

Elevator::State Elevator::getState() const {
    return this->currentState;
}

void Elevator::setUpTimers() {
    this->movingTimer.setSingleShot(true);
    this->floorChangedTimer.setSingleShot(true);
    this->stoppedTimer.setSingleShot(true);
    this->waitingTimer.setSingleShot(true);
}

void Elevator::setUpConnections() {
    connect(&this->movingTimer, SIGNAL(timeout()), this, SLOT(exitedMoving()));
    connect(&this->floorChangedTimer, SIGNAL(timeout()), this, SLOT(exitedFloorChanged()));
    connect(&this->stoppedTimer, SIGNAL(timeout()), this, SLOT(exitedStopped()));
    connect(&this->waitingTimer, SIGNAL(timeout()), this, SLOT(exitedWaiting()));
}

void Elevator::setState(Elevator::State state) {
    this->currentState = state;
    emit stateChanged(state);
}

void Elevator::enteredMoving() {
    if (this->currentState == State::UNDEFINED_WAITING
        || this->currentState == State::FLOOR_CHANGED
        || this->currentState == State::WAITING) {
        this->setState(State::MOVING);
        this->movingTimer.start(TIMER_LARGE);
    }
}

void Elevator::exitedMoving() {
    if (this->currentState == State::MOVING) {
        emit finishedMoving();
    }
}

void Elevator::enteredFloorChanged() {
    if (this->currentState == State::MOVING) {
        this->setState(State::FLOOR_CHANGED);
        this->floorChangedTimer.start(TIMER_SMALL);
    }
}

void Elevator::exitedFloorChanged() {
    if (this->currentState == State::FLOOR_CHANGED) {
        emit finishedFloorChanged();
    }
}

void Elevator::enteredStopped() {
    if (this->currentState == State::FLOOR_CHANGED) {
        this->setState(State::STOPPED);
        this->stoppedTimer.start(TIMER_SMALL);
    }
}

void Elevator::exitedStopped() {
    if (this->currentState == State::STOPPED) {
        emit finishedStopped();
    }
}

void Elevator::enteredWaiting() {
    if (this->currentState == State::STOPPED
        || this->currentState == State::UNDEFINED_WAITING
        || this->currentState == State::WAITING) {
        this->setState(State::WAITING);
        this->waitingTimer.start(TIMER_LARGE);
    }
}

void Elevator::exitedWaiting() {
    if (this->currentState == State::WAITING) {
        emit finishedWaiting();
    }
}

void Elevator::shuttedDown() {
    if (this->currentState == State::WAITING) {
        this->setState(State::UNDEFINED_WAITING);
    }
}
