#include <dataloaders/gpxdataloader.h>
#include <common/exceptions.h>

#include <QFile>
#include <QXmlStreamReader>
#include <QFileInfo>
#include <QDebug>

GPXDataLoader::GPXDataLoader(QString fileName, QString field, QObject *parent)
    : XMLDataLoader(fileName, field, parent)
{
}

GPXDataLoader::~GPXDataLoader()
{
}

void GPXDataLoader::load()
{
    QFileInfo fileInfo(m_fileName);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        throw FileException("file doesn't exist");
    }

    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw FileException("error opening file");
    }

    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError()) {
        inputStream.readNext();
        if (inputStream.isStartElement()) {

            QString field = inputStream.name().toString();
            if (field == m_field) {
                qDebug() << "lon:" << inputStream.attributes().value("lon").toDouble()
                         << "lat:" << inputStream.attributes().value("lat").toDouble();
            }
        }
    }
}

void GPXDataLoader::save()
{

}
