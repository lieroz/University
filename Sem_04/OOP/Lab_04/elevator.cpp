#include "elevator.hpp"

elevator::elevator() {
    create_state(this->undefined_wait, "Lift undefined wait", this->undefined_wait_state_slot(), 0);
    create_state(this->wait, "Lift wait", this->wait_state_slot(), LONG_STATE_TIME);
    create_state(this->move, "Lift move", this->move_state_slot(), LONG_STATE_TIME);
    create_state(this->sudden_stop, "Lift sudden stop", this->sudden_stop_state_slot(), SHORT_STATE_TIME);
    create_state(this->stop, "Lift stop", this->stop_state_slot(), SHORT_STATE_TIME);
    create_state(this->open_doors, "Lift open doors", this->open_doors_state_slot(), SHORT_STATE_TIME);
    create_state(this->close_doors, "Lift close doors", this->close_doors_state_slot(), SHORT_STATE_TIME);
}

const QState* elevator::get_undefined_wait_slot() const {
    return this->undefined_wait;
}

const QState* elevator::get_wait_state() const {
    return this->wait;
}

const QState* elevator::get_move_state() const {
    return this->move;
}

const QState* elevator::get_sudden_stop_state() const {
    return this->sudden_stop;
}

const QState* elevator::get_stop_state() const {
    return this->stop;
}

const QState* elevator::get_open_doors_state() const {
    return this->open_doors;
}

const QState* elevator::get_close_doors_state() const {
    return this->close_doors;
}

void elevator::undefined_wait_state_slot() {

}

void elevator::wait_state_slot() {

}

void elevator::move_state_slot() {

}

void elevator::sudden_stop_state_slot() {

}

void elevator::stop_state_slot() {

}

void elevator::open_doors_state_slot() {

}

void elevator::close_doors_state_slot() {

}
