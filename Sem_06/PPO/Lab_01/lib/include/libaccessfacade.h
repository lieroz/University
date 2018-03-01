#pragma once

#include <dataloaders/dataloaders.h>
#include <common/routestore.h>
#include <common/objectpool.h>

class LibAccessFacade
{
    Q_DISABLE_COPY(LibAccessFacade)

public:
    LibAccessFacade() = default;
    ~LibAccessFacade() = default;

    void load(const QString &fileName, Route &route);
    void addRoute(Route& route);
    void deleteRoute(qint32 index);
    Route &getRoute(qint32 index);

private:
    ObjectPool<AbstractDataLoader> m_pool;
};
