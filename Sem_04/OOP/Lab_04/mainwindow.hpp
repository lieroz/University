#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStateMachine>
#include <QFinalState>
#include <QTimer>
#include <QDebug>

#include <exception>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    protected:
        void create_state(QState*&, const char*, int, int, QState* parent = 0);
        void setUpStateMachine();

    private slots:
        void on_pushButton_clicked();

        void wait_slot();
        void move_slot();
        void stop_slot();
        void open_doors_slot();
        void close_doors_slot();

    private:
        Ui::MainWindow* ui;
        QStateMachine state_machine;

        QState* wait;
        QState* move;
        QState* stop;
        QState* open_doors;
        QState* close_doors;
};

#endif // MAINWINDOW_HPP
