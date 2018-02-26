#include <dataloaders/xmldataloader.h>

XMLDataLoader::XMLDataLoader(QString fileName, QString field, QObject *parent)
    : AbstractDataLoader(fileName, parent), m_field(field)
{
}

XMLDataLoader::~XMLDataLoader()
{
}

void XMLDataLoader::load()
{

}

void XMLDataLoader::save()
{

}
