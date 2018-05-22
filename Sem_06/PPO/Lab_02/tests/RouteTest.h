//
// Created by lieroz on 22.05.18.
//

#ifndef ROUTETEST_H
#define ROUTETEST_H

#include <QTest>

#include <ui/MainWindow.h>

class RouteTest : public QObject
{
    Q_OBJECT
public:
    explicit RouteTest(QObject *parent = nullptr);

private Q_SLOTS:
    void testCreateRoute();
    void testRemoveRoute();

private:
    MainWindow window;
};

#endif // ROUTETEST_H
