#include <libaccessfacade.h>
#include <dataloaders/loaderfactory.h>
#include <common/exceptions.h>

#include <QFileInfo>

LibAccessFacade::LibAccessFacade(QObject *parent) : QObject(parent)
{
    m_store.reset(RouteStore::instance());
}

LibAccessFacade::~LibAccessFacade()
{

}

const Route &LibAccessFacade::load(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        throw FileException("file doesn't exist");
    }

    auto createFunc = LoaderFactory::createDataloader(fileInfo.completeSuffix());
    m_loader.reset(createFunc(fileName));
    m_loader->load();

    return getRoute(m_store->getRoutes().size() - 1);
}

Route &LibAccessFacade::getRoute(qint32 index)
{
    return m_store->getRoute(index);
}

void LibAccessFacade::deleteRoute(qint32 index)
{
    m_store->deleteRoute(index);
}
