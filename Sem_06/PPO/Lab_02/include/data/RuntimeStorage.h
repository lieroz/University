//
// Created by lieroz on 10.05.18.
//

#ifndef LAB_02_RUNTIMESTORAGE_H
#define LAB_02_RUNTIMESTORAGE_H

#include <data/models/Route.h>

class RuntimeStorage
{
public:
    RuntimeStorage(const RuntimeStorage &other) = delete;
    RuntimeStorage(RuntimeStorage &&other) = delete;
    ~RuntimeStorage() = default;

    RuntimeStorage &operator=(const RuntimeStorage &other) = delete;
    RuntimeStorage &operator=(RuntimeStorage &&other) = delete;

    static RuntimeStorage &instance();

    bool addRoute(qint32 index, QSharedPointer<Route> route);
    void addRoute(QSharedPointer<Route> route);
    bool removeRoute(qint32 index);
    void removeRoute();
    QSharedPointer<Route> getRoute(qint32 index);
    const QVector<QSharedPointer<Route> > &getAll();

    qint32 count();

private:
    RuntimeStorage() = default;

    QVector<QSharedPointer<Route>> m_routes;
};

#endif //LAB_02_RUNTIMESTORAGE_H
