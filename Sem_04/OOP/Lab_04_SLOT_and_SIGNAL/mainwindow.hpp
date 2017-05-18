#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QVector>
#include <QPushButton>

#include "ui_mainwindow.h"
#include "controller.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

        const int FLOOR_COUNT = 9;

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    protected:
        void setUpCallButtons();
        void setUpControlButtons();
        void setUpConnections();

    signals:
        void callButtonPressedSignal(int);
        void controlButtonPressedSignal(int);

    public slots:
        void callButtonPressedSlot();
        void controlButtonPressedSlot();

        void setFloor(int);
        void elevatorStateAcceptor(Elevator::State);
        void doorsStateAcceptor(Doors::State);

    private:
        QVector<QPushButton*> callButtons;
        QVector<QPushButton*> controlButtons;

        Controller controller;
        Ui::MainWindow* ui;
};

#endif // MAINWINDOW_HPP
