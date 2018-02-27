#include <QGuiApplication>
#include <QQuickView>
#include <QPointer>

#include <libaccessfacade.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QString filePath = "/home/lieroz/University/Sem_06/PPO/Lab_01/route1.gpx";
    LibAccessFacade facade;
    facade.load(filePath);

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    view.setWidth(640);
    view.setHeight(480);
    view.show();

    return app.exec();
}
