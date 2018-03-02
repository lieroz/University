#pragma once

#include <QTest>

#include <common/routestore.h>

class RouteDeleteTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testRouteDeleteSequential();
    void testRouteDeleteMultithreaded();
};
