#include "doors.hpp"

doors::doors() {
    create_state(this->opening, "Doors opening", this->opening_state_slot(), SHORT_STATE_TIME);
    create_state(this->opened, "Doors opened", this->opened_state_slot(), SHORT_STATE_TIME);
    create_state(this->closing, "Doors closing", this->closing_state_slot(), SHORT_STATE_TIME);
    create_state(this->closed, "Doors closed", this->closed_state_slot(), SHORT_STATE_TIME);
}

const QState* doors::get_opening_state() const {
    return this->opening;
}

const QState* doors::get_opened_state() const {
    return this->opened;
}

const QState* doors::get_closing_state() const {
    return this->closing;
}

const QState* doors::get_closed_state() const {
    return this->closed;
}

void doors::opening_state_slot() {

}

void doors::opened_state_slot() {

}

void doors::closing_state_slot() {

}

void doors::closed_state_slot() {

}
