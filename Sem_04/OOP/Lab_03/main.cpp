#include <QApplication>

#include "gui/mainwindow.hpp"
#include "facade/facade.hpp"
#include "commands/command.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    facade f;
    upload_view c1("/home/lieroz/University/Sem_04/OOP/Lab_03/DATA/cube.json");
    f.execute_command(c1);
    delete_view c2(0);
    f.execute_command(c2);
    add_model c3(0);
    f.execute_command(c3);
    remove_model c4(0);
    f.execute_command(c4);

    return application.exec();
}
