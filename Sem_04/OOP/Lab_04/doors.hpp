#ifndef DOORS_HPP
#define DOORS_HPP

#include "object.hpp"

class doors : public object {
        Q_OBJECT
    public:
        doors();
        ~doors() = default;

        const QState* get_opening_state() const;
        const QState* get_opened_state() const;
        const QState* get_closing_state() const;
        const QState* get_closed_state() const;

    public slots:
        void opening_state_slot();
        void opened_state_slot();
        void closing_state_slot();
        void closed_state_slot();

    private:
        QState* opening;
        QState* opened;
        QState* closing;
        QState* closed;
};

#endif // DOORS_HPP
