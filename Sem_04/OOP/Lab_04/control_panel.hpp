#ifndef CONTROL_PANEL_HPP
#define CONTROL_PANEL_HPP

#include "object.hpp"

class control_panel : public object {
    public:
        control_panel() = default;
        ~control_panel() = default;

    signals:
        void floor_button_pressed();
        void stop_button_pressed();
        void lift_call_button_pressed();
};

#endif // CONTROL_PANEL_HPP
