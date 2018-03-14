#include <libaccessfacade.h>

#include <QFileInfo>

#include <dataloaders/loaderfactory.h>
#include <common/exceptions.h>

void LibAccessFacade::load(const QString &fileName, Route &route)
{
    QFileInfo fileInfo(fileName);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        throw FileException("file doesn't exist");
    }

    auto loadFunc = LoaderFactory::getDataloader(fileInfo.completeSuffix());
    loadFunc(fileName, route);
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
