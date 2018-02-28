#pragma once

#include <QObject>
#include <QScopedPointer>

#include <dataloaders/dataloaders.h>
#include <common/routestore.h>

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
    QScopedPointer<AbstractDataLoader> m_loader;
    QScopedPointer<RouteStore> m_store;
};
