#include <QGuiApplication>
#include <QQuickView>
#include <QPointer>

#include <dataloaders/abstractdataloader.h>
#include <dataloaders/gpxdataloader.h>
#include <3dparty/polyline/polylineencoder.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    view.setWidth(360);
    view.setHeight(640);
    view.show();

    return app.exec();
}
