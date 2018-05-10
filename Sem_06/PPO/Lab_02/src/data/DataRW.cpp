//
// Created by lieroz on 10.05.18.
//

#include <QFile>
#include <QXmlStreamReader>
#include <QVector>
#include <QMap>

#include <data/DataRW.h>
#include <data/models/Route.h>

QSharedPointer<Route> readGpx(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    QXmlStreamReader inputStream(&file);
    QString currentField;
    qreal dist = 0;

    QString name;
    QVector<Coordinate> path;
    while (!inputStream.atEnd() && !inputStream.hasError()) {
        inputStream.readNext();

        if (inputStream.isStartElement()) {
            currentField = inputStream.name().toString();

            if (currentField == "name") {
                name = inputStream.readElementText();
            }

            if (currentField == "trkpt") {
                const auto lat = inputStream.attributes().value("lat").toDouble();
                const auto lon = inputStream.attributes().value("lon").toDouble();
                Coordinate coord(lat, lon, 0);

                if (!path.isEmpty()) {
                    dist += path.back().distanceTo(coord);
                }
                path.append(coord);
            }
        }
    }

    return QSharedPointer::create(Route(name, path));
}

bool writeGpx(const QString &fileName, QSharedPointer<Route> route)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("trk");

    xmlWriter.writeStartElement("name");
    xmlWriter.writeCharacters(route->getName());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("trkseg");

    for (auto &coordinate : route->getPath()) {
        xmlWriter.writeStartElement("trkpt");
        xmlWriter.writeAttribute("lat", QString::number(coordinate.getLatitude()));
        xmlWriter.writeAttribute("lon", QString::number(coordinate.getLongitude()));
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    return true;
}

typedef std::function<QSharedPointer<Route>(const QString &)> rFunc;
typedef std::function<bool(const QString &, QSharedPointer<Route>)> wFunc;

QMap<QString, QPair<rFunc, wFunc>> registeredFileTypes = {
        {"gpx", qMakePair(readGpx, writeGpx)}
};

QPair<rFunc, wFunc> getRWFunctions(const QString &fileType)
{
    if (registeredFileTypes.find(fileType) != registeredFileTypes.end()) {
        return registeredFileTypes[fileType];
    }
    return nullptr;
};
