#include <QApplication>
#include <QQmlApplicationEngine>

#include <gui/mainwindow.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<MapViewProxy>("MyLibrary", 1, 0, "MapViewProxy");

    MainWindow w;
    w.show();

    return app.exec();
}
