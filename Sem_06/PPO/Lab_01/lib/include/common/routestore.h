#pragma once

#include <QReadWriteLock>
#include <QAtomicPointer>
#include <QVector>
#include <QMutex>

#include <common/route.h>

class RouteStore
{
    Q_DISABLE_COPY(RouteStore)
    RouteStore() = default;

public:
    ~RouteStore() = default;

    static RouteStore *instance();

    void addRoute(Route &route);
    void addRoutes(QVector<Route> &routes);

    void insertRoute(qint32 index, Route &route);
    void insertRoutes(qint32 index, QVector<Route> &routes);

    void deleteRoute(qint32 index);
    void deleteRoutes(qint32 index, qint32 n);

    Route &getRoute(qint32 index);
    QVector<Route> &getRoutes();

    qint32 size() const;
    bool isEmpty() const;

private:
    static QAtomicPointer<RouteStore> m_instance;
    static QMutex m_mutex;
    QVector<Route> m_routes;
    QReadWriteLock m_rwlock;
};
