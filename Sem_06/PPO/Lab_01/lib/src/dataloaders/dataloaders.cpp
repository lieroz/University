#include <dataloaders/dataloaders.h>

#include <QFile>
#include <QXmlStreamReader>

#include <common/exceptions.h>
#include <common/routestore.h>

void GpxDataLoader::load(const QString &fileName, Route &route)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw FileException("error opening file");
    }

    QXmlStreamReader inputStream(&file);
    QString currentField;
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
}
