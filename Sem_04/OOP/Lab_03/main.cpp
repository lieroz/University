#include <QApplication>

#include "gui/mainwindow.hpp"
#include "container/vector/vector.hpp"
#include "container/matrix/matrix.hpp"
#include "upload/uploader.hpp"
#include "primitives/point3d.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    point3d<int> pt;

    return application.exec();
}
