#include <QApplication>

#include "gui/mainwindow.hpp"
#include "container/vector/vector.hpp"
#include "container/matrix/matrix.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    return application.exec();
}
