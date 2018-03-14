#include <common/routestore.h>

QAtomicPointer<RouteStore> RouteStore::m_instance;
QMutex RouteStore::m_mutex;

RouteStore *RouteStore::instance()
{
    RouteStore *tmp = m_instance.loadAcquire();

    if (tmp == Q_NULLPTR) {
        QMutexLocker guard(&m_mutex);
        tmp = m_instance.load();

        if (tmp == Q_NULLPTR) {
            tmp = new RouteStore();
            m_instance.storeRelease(tmp);
        }
    }

    return tmp;
}

void RouteStore::addRoute(QSharedPointer<Route> route)
{
    QWriteLocker guard(&m_rwlock);
    m_routes.append(route);
}

void RouteStore::addRoutes(QVector<QSharedPointer<Route>> &routes)
{
    QWriteLocker guard(&m_rwlock);
    m_routes.append(routes);
}

void RouteStore::insertRoute(qint32 index, QSharedPointer<Route> route)
{
    QWriteLocker guard(&m_rwlock);
    m_routes.insert(index, route);
}

void RouteStore::insertRoutes(qint32 index, QVector<QSharedPointer<Route>> &routes)
{
    QWriteLocker guard(&m_rwlock);

    Q_FOREACH (QSharedPointer<Route> route, routes) {
        m_routes.insert(index++, route);
    }
}

void RouteStore::deleteRoute(qint32 index)
{
    QWriteLocker guard(&m_rwlock);
    m_routes.remove(index);
}

void RouteStore::deleteRoutes(qint32 index, qint32 n)
{
    QWriteLocker guard(&m_rwlock);
    m_routes.remove(index, n);
}

QSharedPointer<Route> RouteStore::getRoute(qint32 index)
{
    QReadLocker guard(&m_rwlock);
    return m_routes[index];
}

QVector<QSharedPointer<Route>> &RouteStore::getRoutes()
{
    QReadLocker guard(&m_rwlock);
    return m_routes;
}

qint32 RouteStore::size() const
{
    return m_routes.size();
}

bool RouteStore::isEmpty() const
{
    return m_routes.isEmpty();
}
