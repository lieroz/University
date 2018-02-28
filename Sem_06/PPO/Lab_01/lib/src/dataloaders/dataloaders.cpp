#include <dataloaders/dataloaders.h>
#include <common/exceptions.h>

#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <common/routestore.h>

AbstractDataLoader::AbstractDataLoader(const QString &fileName, QObject *parent)
    : m_fileName(fileName), QObject(parent)
{
}

AbstractDataLoader::~AbstractDataLoader()
{
}

/******************************************************************************
** GPXDataLoader
*/

GpxDataLoader::GpxDataLoader(const QString &fileName, QObject *parent)
    : AbstractDataLoader(fileName, parent)
{
}

GpxDataLoader::~GpxDataLoader()
{
}

void GpxDataLoader::load()
{
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw FileException("error opening file");
    }

    QXmlStreamReader inputStream(&file);
    QString currentField;
    Route route;
    qreal dist = 0;

    while (!inputStream.atEnd() && !inputStream.hasError()) {
        inputStream.readNext();

        if (inputStream.isStartElement()) {
            currentField = inputStream.name().toString();

            if (currentField == "name") {
                route.setName(inputStream.readElementText());
            }

            if (currentField == "trkpt") {
                const auto lat = inputStream.attributes().value("lat").toDouble();
                const auto lon = inputStream.attributes().value("lon").toDouble();
                QGeoCoordinate coord(lat, lon);

                if (!route.getCoordinates().isEmpty()) {
                    const auto count = route.getCoordinates().size();
                    dist += route.getCoordinates().coordinateAt(count - 1).distanceTo(coord);
                }

                route.appendCoordinate(coord);
            }
        }
    }

    route.setLength(dist);
    RouteStore::instance()->addRoute(route);
}
