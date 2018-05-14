//
// Created by lieroz on 10.05.18.
//

#include <data/RuntimeStorage.h>

RuntimeStorage &RuntimeStorage::instance()
{
    static RuntimeStorage instance;
    return instance;
}

bool RuntimeStorage::addRoute(qint32 index, QSharedPointer<Route> route)
{
    if (index < 0 || index > m_routes.size()) {
        return false;
    }
    m_routes.insert(std::begin(m_routes) + index, route);
    return true;
}

void RuntimeStorage::addRoute(QSharedPointer<Route> route)
{
    m_routes.push_back(route);
}

bool RuntimeStorage::removeRoute(qint32 index)
{
    if (index < 0 || index >= m_routes.size()) {
        return false;
    }
    m_routes.erase(std::begin(m_routes) + index);
    return true;
}

void RuntimeStorage::removeRoute()
{
    m_routes.pop_back();
}

QSharedPointer<Route> RuntimeStorage::getRoute(qint32 index)
{
    if (index < 0 || index >= m_routes.size()) {
        return nullptr;
    }
    return m_routes[index];
}

qint32 RuntimeStorage::count()
{
    return m_routes.count();
}
