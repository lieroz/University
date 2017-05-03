#ifndef STATEFACTORY_HPP
#define STATEFACTORY_HPP

#include <QState>
#include <QTimer>
#include <QFinalState>

class object : public QObject {
        Q_OBJECT
    public:
        object() = default;
        ~object() = default;

        QState* create_state(QState*, const char*, const char*, int, QState* parent = 0);

    protected:
        const int SHORT_STATE_TIME = 1000;
        const int LONG_STATE_TIME = 3000;

    private:
        static size_t state_count;

};

#endif // STATEFACTORY_HPP
