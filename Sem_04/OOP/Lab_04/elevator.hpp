#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <QWidget>
#include <QQueue>
#include <QVector>
#include <QPushButton>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QTimer>

namespace Ui {
    class Elevator;
}

class Elevator : public QWidget {
        Q_OBJECT

        const int FLOOR_COUNT = 9;
        const int BIG_TIMER_COUNT = 3000;
        const int MID_TIMER_COUNT = 2000;
        const int SMALL_TIMER_COUNT = 1000;

    public:
        explicit Elevator(QWidget* parent = 0);
        ~Elevator();

    protected:
        void create_state(QState*&, QString, int, QState* parent = 0);

        void set_up_call_button_signals();
        void set_up_manage_button_signals();
        void declare_states();
        void set_up_transitions();
        void set_up_machine();

    signals:
        void queue_empty();
        void queue_filled_different_floor();
        void queue_filled_same_floor();

        void arrived();
        void moving();

    private slots:
        void call_lift_button_pressed();
        void manage_lift_button_pressed();
        void stop_button_pressed();

        void check_queue_slot();
        void check_floor_slot();

    private:
        Ui::Elevator* ui;
        QVector<QPushButton*> call_buttons;
        QVector<QPushButton*> manage_buttons;
        QQueue<int> call_states;
        QQueue<int> manage_states;

        QState* move;
        QState* floor_change;
        QState* stop;
        QState* open;
        QState* opening;
        QState* opened;
        QState* wait;
        QState* close;
        QState* closing;
        QState* closed;
        QState* sudden_stop;

        QState* s1;
        QState* s2;
        QState* interim_state;
        QFinalState* undefined_wait;

        QStateMachine machine;

        int current_floor = 1;
        int destination_floor = 1;
};

#endif // ELEVATOR_HPP
