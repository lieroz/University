#ifndef DOORS_HPP
#define DOORS_HPP

#include <QObject>
#include <QTimer>

#include "config.hpp"

class Doors : public QObject {
        Q_OBJECT

    public:
        enum class State {
            OPENING, OPENED, CLOSING, CLOSED,
        };

        explicit Doors(QObject* parent = 0);

        State getState() const;

    protected:
        void setUpTimers();
        void setUpConnections();
        void setState(State);

    signals:
        void finishedOpening();
        void finishedOpened();
        void finishedClosing();
        void finishedClosed();

        void stateChanged(Doors::State);

    public slots:
        void enteredOpening();
        void exitedOpening();

        void enteredOpened();
        void exitedOpened();

        void enteredClosing();
        void exitedClosing();

        void enteredClosed();
        void exitedClosed();

    private:
        State currentState = State::CLOSED;

        QTimer openingTimer;
        QTimer openedTimer;
        QTimer closingTimer;
        QTimer closedTimer;
};

#endif // DOORS_HPP
