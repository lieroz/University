//
// Created by lieroz on 10.05.18.
//

#include <QFile>
#include <QXmlStreamReader>
#include <QVector>
#include <QMap>

#include <data/DataRW.h>
#include <data/models/Route.h>
#include <data/Polyline.h>

#include <QDebug>

QSharedPointer<Route> readGpx(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    QXmlStreamReader inputStream(&file);
    QString currentField, prevField;
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

            if (currentField == "ele" && prevField == "trkpt") {
                const auto alt = inputStream.readElementText().toDouble();
                path[path.count() - 1].setAltitude(alt);
            }

            prevField = currentField;
        }
    }

    file.close();
    return QSharedPointer<Route>::create(Route(name, path));
}

bool writeGpx(QFile &file, QSharedPointer<Route> route)
{
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
        xmlWriter.writeStartElement("ele");
        xmlWriter.writeCharacters(QString::number(coordinate.getAltitude()));
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    return true;
}

QSharedPointer<Route> readPolyline(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    QTextStream stream(&file);
    QString polyline;
    stream >> polyline;
    file.close();
    return Polyline::decode(polyline);
}

bool writePolyline(QFile &file, QSharedPointer<Route> route)
{
    QTextStream stream(&file);
    stream << Polyline::encode(route);
    file.close();
    return true;
}

QMap<QString, std::pair<rFunc, wFunc>> registeredFileTypes = {
    {"gpx", std::make_pair(readGpx, writeGpx)},
    {"txt", std::make_pair(readPolyline, writePolyline)}
};

std::pair<rFunc, wFunc> getRWFunctions(const QString &fileType)
{
    if (registeredFileTypes.find(fileType) != registeredFileTypes.end()) {
        return registeredFileTypes[fileType];
    }
    return std::make_pair(nullptr, nullptr);
}
