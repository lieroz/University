#include <QApplication>

#include "gui/mainwindow.hpp"
#include "facade/facade.hpp"
#include "commands/command.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    facade f;
    commands::upload_view c1("/home/lieroz/University/Sem_04/OOP/Lab_03/DATA/cube.json");
    f.execute_command(c1);
//    commands::delete_view c2(0);
//    f.execute_command(c2);
    commands::add_model c3(0);
    f.execute_command(c3);
//    commands::remove_model c4(0);
//    f.execute_command(c4);
    commands::move_model_OX c5(10);
    f.execute_command(c5);



    return application.exec();
}
