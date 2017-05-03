#include "object.hpp"

size_t object::state_count = 0;

QState* object::create_state(QState* state, const char* name, const char* slot, int duration, QState* parent) {
    state = new QState(parent);
    QTimer* timer = new QTimer(state);
    timer->setInterval(duration);
    timer->setSingleShot(true);
    QState* timing = new QState(state);
    connect(timing, SIGNAL(entered()), this, SLOT(slot));
    connect(timing, SIGNAL(entered()), timer, SLOT(start()));
    QFinalState* done = new QFinalState(state);
    timing->addTransition(timer, SIGNAL(timeout()), done);
    state->setInitialState(timing);
    state->setObjectName(name);
    ++object::state_count;
}
