#pragma once

#include <dataloaders/dataloaders.h>
#include <common/routestore.h>

class LibAccessFacade
{
    Q_DISABLE_COPY(LibAccessFacade)

public:
    LibAccessFacade() = default;
    ~LibAccessFacade() = default;

    void load(const QString &fileName, QSharedPointer<Route> route);
    void addRoute(QSharedPointer<Route> route);
    void deleteRoute(qint32 index);
    QSharedPointer<Route> getRoute(qint32 index);
};
