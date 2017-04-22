#include <QApplication>

#include "gui/mainwindow.hpp"
#include "gui/canvasgl.hpp"
#include "facade/facade.hpp"
#include "commands/command.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();

//    CanvasGL canvas;
//    canvas.show();

//    facade f;
//    commands::upload_view c1("/home/lieroz/University/Sem_04/OOP/Lab_03/DATA/cube.json");
//    f.execute_command(c1);
//    commands::delete_view c2(0);
//    f.execute_command(c2);
//    commands::add_model c3(0);
//    f.execute_command(c3);
//    f.execute_command(c3);
//    commands::remove_model c4(0);
//    f.execute_command(c4);
//    point3d<double> move_coords(10, 11, 23);
//    commands::move c5(move_coords, -1);
//    f.execute_command(c5);

//    commands::rotate_model_OX c6(14, -1);
//    f.execute_command(c6);

//    commands::scale c6(2, -1);
//    f.execute_command(c6);

    return application.exec();
}
