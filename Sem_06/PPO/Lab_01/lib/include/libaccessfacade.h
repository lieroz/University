#pragma once

#include <QObject>

#include <dataloaders/dataloaders.h>
#include <common/routestore.h>
#include <common/objectpool.h>

class LibAccessFacade : public QObject
{
public:
    LibAccessFacade(QObject *parent = Q_NULLPTR);
    ~LibAccessFacade();

    const Route &load(const QString &fileName);

    void addRoute(const Route& route);
    void deleteRoute(qint32 index);
    Route &getRoute(qint32 index);

private:
    QScopedPointer<RouteStore> m_store;
    ObjectPool<AbstractDataLoader> m_pool;
};
