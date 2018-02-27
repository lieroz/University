#pragma once

#include <common/route.h>

#include <QObject>
#include <QReadWriteLock>
#include <QAtomicPointer>
#include <QMutex>

class RouteStore : public QObject
{
public:
    ~RouteStore();

    static RouteStore *instance();

    void addRoute(const Route &route);
    void addRoutes(const QVector<Route> &routes);

    void insertRoute(qint32 index, const Route &route);
    void insertRoutes(qint32 index, const QVector<Route> &routes);

    void deleteRoute(qint32 index);
    void deleteRoutes(qint32 index, qint32 n);

    Route &getRoute(qint32 index);
    QVector<Route> &getRoutes();

private:
    RouteStore(QObject *parent = Q_NULLPTR);
    RouteStore(const RouteStore &) = delete;
    RouteStore(RouteStore &&) = delete;

    RouteStore &operator=(const RouteStore &) = delete;
    RouteStore &operator=(RouteStore &&) = delete;

private:
    static QAtomicPointer<RouteStore> m_instance;
    static QMutex m_mutex;
    QVector<Route> m_routes;
    QReadWriteLock m_rwlock;
};
