#include "elevator.hpp"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Elevator window;
    window.show();

    return app.exec();
}
