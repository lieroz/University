#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QStateMachine>

#include "elevator.hpp"
#include "control_panel.hpp"

class controller {
    public:
        controller();

    private:
        elevator lift;
        control_panel panel;
        QStateMachine machine;
};

#endif // CONTROLLER_HPP
