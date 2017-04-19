#include <QApplication>

#include "gui/mainwindow.hpp"
#include "upload/uploader.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    uploader load(std::string("/home/lieroz/University/Sem_04/OOP/Lab_03/gui/cube.json"));
    load.open();
    load.serialize_json();
    load.close();
    model m = load.deserialize_json();

    return application.exec();
}
