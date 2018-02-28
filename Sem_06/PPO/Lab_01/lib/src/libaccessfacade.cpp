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

    if (m_pool.isEmpty()) {
        auto createFunc = LoaderFactory::createDataloader(fileInfo.completeSuffix());
        QSharedPointer<AbstractDataLoader> loader(createFunc(fileName));
        loader->load();
        m_pool.put(loader);
    } else {
        auto loader = m_pool.take();
        loader->reset(fileName);
        loader->load();
        m_pool.put(loader);
    }

    return getRoute(m_store->getRoutes().size() - 1);
}

void LibAccessFacade::addRoute(const Route &route)
{
    m_store->addRoute(route);
}

Route &LibAccessFacade::getRoute(qint32 index)
{
    return m_store->getRoute(index);
}

void LibAccessFacade::deleteRoute(qint32 index)
{
    m_store->deleteRoute(index);
}
