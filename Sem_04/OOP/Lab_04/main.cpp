#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(110, 300);
    window.show();

    return app.exec();
}
