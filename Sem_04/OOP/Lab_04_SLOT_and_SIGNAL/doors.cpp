#include "doors.hpp"

Doors::Doors(QObject* parent) : QObject(parent) {
    this->setUpTimers();
    this->setUpConnections();
}

Doors::State Doors::getState() const {
    return this->currentState;
}

void Doors::setUpTimers() {
    this->openingTimer.setSingleShot(true);
    this->openedTimer.setSingleShot(true);
    this->closingTimer.setSingleShot(true);
    this->closedTimer.setSingleShot(true);
}

void Doors::setUpConnections() {
    connect(&this->openingTimer, SIGNAL(timeout()), this, SLOT(exitedOpening()));
    connect(this, SIGNAL(finishedOpening()), this, SLOT(enteredOpened()));
    connect(&this->openedTimer, SIGNAL(timeout()), this, SLOT(exitedOpened()));
    connect(&this->closingTimer, SIGNAL(timeout()), this, SLOT(exitedClosing()));
    connect(this, SIGNAL(finishedClosing()), this, SLOT(enteredClosed()));
    connect(&this->closedTimer, SIGNAL(timeout()), this, SLOT(exitedClosed()));
}

void Doors::setState(Doors::State state) {
    this->currentState = state;
    emit stateChanged(state);
}

void Doors::enteredOpening() {
    if (this->currentState == State::CLOSED) {
        this->setState(State::OPENING);
        this->openingTimer.start(TIMER_MID);
    }
}

void Doors::exitedOpening() {
    if (this->currentState == State::OPENING) {
        emit finishedOpening();
    }
}

void Doors::enteredOpened() {
    if (this->currentState == State::OPENING) {
        this->setState(State::OPENED);
        this->openedTimer.start(TIMER_SMALL);
    }
}

void Doors::exitedOpened() {
    if (this->currentState == State::OPENED) {
        emit finishedOpened();
    }
}

void Doors::enteredClosing() {
    if (this->currentState == State::OPENED) {
        this->setState(State::CLOSING);
        this->closingTimer.start(TIMER_MID);
    }
}

void Doors::exitedClosing() {
    if (this->currentState == State::CLOSING) {
        emit finishedClosing();
    }
}

void Doors::enteredClosed() {
    if (this->currentState == State::CLOSING) {
        this->setState(State::CLOSED);
        this->closedTimer.start(TIMER_SMALL);
    }
}

void Doors::exitedClosed() {
    if (this->currentState == State::CLOSED) {
        emit finishedClosed();
    }
}
