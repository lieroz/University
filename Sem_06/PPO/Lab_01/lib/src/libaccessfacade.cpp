#include <libaccessfacade.h>
#include <dataloaders/loaderfactory.h>
#include <common/exceptions.h>

#include <QFileInfo>

void LibAccessFacade::load(const QString &fileName, Route &route)
{
    QFileInfo fileInfo(fileName);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        throw FileException("file doesn't exist");
    }

    QSharedPointer<AbstractDataLoader> loader;

    if (m_pool.isEmpty()) {
        auto createFunc = LoaderFactory::createDataloader(fileInfo.completeSuffix());
        QSharedPointer<AbstractDataLoader> tmp(createFunc(fileName));
        loader.swap(tmp);
    } else {
        loader = m_pool.take();
        loader->reset(fileName);
    }

    loader->load(route);
    m_pool.put(loader);
}

void LibAccessFacade::addRoute(Route &route)
{
    RouteStore::instance()->addRoute(route);
}

Route &LibAccessFacade::getRoute(qint32 index)
{
    return RouteStore::instance()->getRoute(index);
}

void LibAccessFacade::deleteRoute(qint32 index)
{
    RouteStore::instance()->deleteRoute(index);
}
