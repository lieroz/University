#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <QObject>
#include <QTimer>

#include "config.hpp"

class Elevator : public QObject  {
        Q_OBJECT

    public:
        enum class State {
            MOVING, FLOOR_CHANGED, STOPPED, WAITING, UNDEFINED_WAITING,
        };

        explicit Elevator(QObject* parent = 0);

        State getState() const;

    protected:
        void setUpTimers();
        void setUpConnections();
        void setState(State);

    signals:
        void finishedMoving();
        void finishedFloorChanged();
        void finishedStopped();
        void finishedWaiting();

        void stateChanged(Elevator::State);

    public slots:
        void enteredMoving();
        void exitedMoving();

        void enteredFloorChanged();
        void exitedFloorChanged();

        void enteredStopped();
        void exitedStopped();

        void enteredWaiting();
        void exitedWaiting();

        void shuttedDown();

    private:
        State currentState = State::UNDEFINED_WAITING;

        QTimer movingTimer;
        QTimer floorChangedTimer;
        QTimer stoppedTimer;
        QTimer waitingTimer;
};

#endif // ELEVATOR_HPP
