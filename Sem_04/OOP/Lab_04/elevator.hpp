#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include "object.hpp"
#include "doors.hpp"

class elevator : public object {
        Q_OBJECT
    public:
        elevator() = default;
        ~elevator() = default;

        const QState* get_undefined_wait_slot() const;
        const QState* get_wait_state() const;
        const QState* get_move_state() const;
        const QState* get_sudden_stop_state() const;
        const QState* get_stop_state() const;
        const QState* get_open_doors_state() const;
        const QState* get_close_doors_state() const;

    public slots:
        void undefined_wait_state_slot();
        void wait_state_slot();
        void move_state_slot();
        void sudden_stop_state_slot();
        void stop_state_slot();
        void open_doors_state_slot();
        void close_doors_state_slot();

    private:
        QState* undefined_wait;
        QState* wait;
        QState* move;
        QState* sudden_stop;
        QState* stop;
        QState* open_doors;
        QState* close_doors;

        doors drs;
};

#endif // ELEVATOR_HPP
