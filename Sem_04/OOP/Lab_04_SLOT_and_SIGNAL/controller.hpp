#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QQueue>

#include "doors.hpp"
#include "elevator.hpp"

class Controller : public QObject {
        Q_OBJECT

    public:
        explicit Controller(QObject* parent = 0);

    protected:
        void setUpConnections();

    signals:
        void move();
        void changeFloor();
        void stop();
        void open();
        void close();
        void shutDown();

        void setFloor(int);
        void elevatorStateChanged(Elevator::State, bool);
        void doorsStateChanged(Doors::State);

    public slots:
        void callButtonPressed(int);
        void controlButtonPressed(int);

        void finishedMoving();
        void finishedFloorChanged();
        void finishedStopped();
        void finishedClosed();

        void elevatorStateChangedAcceptor(Elevator::State);
        void doorsStateChangedAcceptor(Doors::State);

    private:
        Doors doors;
        Elevator elevator;

        QQueue<int> callSignals;
        QQueue<int> controlSignals;

        int currentFloor = 1;
        int destinationFloor = 1;
};

#endif // CONTROLLER_HPP
