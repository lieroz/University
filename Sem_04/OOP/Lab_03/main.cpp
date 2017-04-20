#include <QApplication>

#include "gui/mainwindow.hpp"
#include "facade/facade.hpp"
#include "commands/command.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    facade f;
    load_model comm(std::string("/home/lieroz/University/Sem_04/OOP/Lab_03/gui/cube.json"));
    f.execute_command(comm);

    return application.exec();
}
