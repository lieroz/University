#pragma once

#include <common/route.h>

#include <QObject>
#include <QReadWriteLock>

class RouteStore : public QObject
{
public:
    RouteStore(QObject *parent = Q_NULLPTR);
    ~RouteStore();

    void addRoute(const Route &route);
    void addRoutes(const QVector<Route> &routes);

    void deleteRoute(qint32 index);
    void deleteRoutes(qint32 index, qint32 n);

    const QVector<Route> &getRoutes();

private:
    QVector<Route> m_routes;
    QReadWriteLock m_rwlock;
};
