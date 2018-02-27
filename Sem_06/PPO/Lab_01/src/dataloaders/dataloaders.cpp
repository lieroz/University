#include <dataloaders/dataloaders.h>
#include <common/exceptions.h>

#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

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
    while (!inputStream.atEnd() && !inputStream.hasError()) {
        inputStream.readNext();
        if (inputStream.isStartElement()) {

            QString field = inputStream.name().toString();
            if (field == "trkpt") {
                qDebug() << "lon:" << inputStream.attributes().value("lon").toDouble()
                         << "lat:" << inputStream.attributes().value("lat").toDouble();
            }
        }
    }
}

void GpxDataLoader::save()
{

}
