#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPointer>

#include "ui_mainwindow.h"
#include "controller.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    protected:
        void setUpCallButtons();
        void setUpControlButtons();
        void setUpConnections();

        void paintEvent(QPaintEvent*) override;

        void updateElevator(bool);
        void updateDoorsOpening();
        void updateDoorsClosing();

    signals:
        void callButtonPressedSignal(int);
        void controlButtonPressedSignal(int);

    public slots:
        void callButtonPressedSlot();
        void controlButtonPressedSlot();

        void setFloor(int);
        void elevatorStateAcceptor(Elevator::State, bool);
        void doorsStateAcceptor(Doors::State);

    private:
        QVector<QPushButton*> callButtons;
        QVector<QPushButton*> controlButtons;

        Controller controller;
        QPointer<QPropertyAnimation> elevatorAnimation;
        QPointer<QPropertyAnimation> leftDoorAnimation;
        QPointer<QPropertyAnimation> rightDoorAnimation;
        Ui::MainWindow* ui;

        int increment;
        int leftDoorWidth;
        int rightDoorWidth;
};

#endif // MAINWINDOW_HPP
