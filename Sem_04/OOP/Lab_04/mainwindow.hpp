#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QQueue>
#include <QVector>
#include <QPushButton>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QTimer>
#include <QSignalTransition>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    protected:
        void create_state(QState*&, QString, int, QState* parent = 0);
        void set_up_call_button_signals();
        void set_up_manage_button_signals();
        void declare_states();
        void set_up_transitions();
        void set_up_machine();

    signals:
        void call_button_clicked(int);
        void manage_button_clicked(int);

        void queue_empty();
        void queue_filled();

    private slots:
        void call_lift_button_clicked();
        void manage_lift_button_clicked();
        void check_slot();

    private:
        Ui::MainWindow* ui;
        QVector<QPushButton*> call_buttons;
        QVector<QPushButton*> manage_buttons;
        QQueue<const char*> queued_signals;

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
        QState* interim_state;
        QFinalState* undefined_wait;

        QState* s1; // When elevator has to move to the floor
        QState* s2; // When elevator doesn't have to move

        QStateMachine machine;

        const size_t FLOOR_COUNT = 9;
        int current_floor = 1;
};

#endif // MAINWINDOW_HPP
