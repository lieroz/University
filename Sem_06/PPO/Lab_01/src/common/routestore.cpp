#include <common/routestore.h>

RouteStore::RouteStore(QObject *parent) : QObject(parent)
{

}

RouteStore::~RouteStore()
{

}

void RouteStore::addRoute(const Route &route)
{
    QWriteLocker guard(&m_rwlock);
    m_routes.append(route);
}

void RouteStore::addRoutes(const QVector<Route> &routes)
{
    QWriteLocker guard(&m_rwlock);
    m_routes.append(routes);
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

const QVector<Route> &RouteStore::getRoutes()
{
    QReadLocker guard(&m_rwlock);
    return m_routes;
}
