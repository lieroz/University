#include <QGuiApplication>
#include <QQuickView>
#include <QPointer>

#include <dataloaders/abstractdataloader.h>
#include <dataloaders/gpxdataloader.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

//    QString filePath = "/home/lieroz/University/Sem_06/PPO/Lab_01/route1.gpx";
//    QPointer<AbstractDataLoader> loader = new GPXDataLoader(filePath, "trkpt");
//    loader->load();

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    view.setWidth(360);
    view.setHeight(640);
    view.show();

    return app.exec();
}
