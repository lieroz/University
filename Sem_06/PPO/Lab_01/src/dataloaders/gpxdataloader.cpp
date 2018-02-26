#include <dataloaders/gpxdataloader.h>
#include <exceptions/fileexception.h>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

GPXDataLoader::GPXDataLoader(QString fileName, QObject *parent)
    : XMLDataLoader(fileName, parent)
{
}

GPXDataLoader::~GPXDataLoader()
{
}

void GPXDataLoader::load()
{
    QFile file(m_fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw FileException("error opening file");
    }

    QXmlStreamReader inputStream(&file);

    while (!inputStream.atEnd() && !inputStream.hasError()) {
        inputStream.readNext();

        if (inputStream.isStartElement()) {
            QString name = inputStream.name().toString();

            if (name == "trkpt") {
                qDebug() << "lon:" << inputStream.attributes().value("lon").toDouble()
                         << "lat:" << inputStream.attributes().value("lat").toDouble();
            }
        }
    }
}

void GPXDataLoader::save()
{

}
