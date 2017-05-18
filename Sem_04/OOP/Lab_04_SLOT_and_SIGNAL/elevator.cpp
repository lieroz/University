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
    this->setState(State::MOVING);
    this->movingTimer.start(TIMER_LARGE);
}

void Elevator::exitedMoving() {
    emit finishedMoving();
}

void Elevator::enteredFloorChanged() {
    this->setState(State::FLOOR_CHANGED);
    this->floorChangedTimer.start(TIMER_SMALL);
}

void Elevator::exitedFloorChanged() {
    emit finishedFloorChanged();
}

void Elevator::enteredStopped() {
    this->setState(State::STOPPED);
    this->stoppedTimer.start(TIMER_SMALL);
}

void Elevator::exitedStopped() {
    emit finishedStopped();
}

void Elevator::enteredWaiting() {
    this->setState(State::WAITING);
    this->waitingTimer.start(TIMER_LARGE);
}

void Elevator::exitedWaiting() {
    emit finishedWaiting();
}

void Elevator::shuttedDown() {
    this->setState(State::UNDEFINED_WAITING);
}
