#include <QApplication>

#include <ui/MainWindow.h>
#include <data/Polyline.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
