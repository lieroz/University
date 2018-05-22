//
// Created by lieroz on 22.05.18.
//

#ifndef LOADDATATEST_H
#define LOADDATATEST_H

#include <QTest>

#include <ui/MainWindow.h>

class LoadDataTest : public QObject
{
    Q_OBJECT
public:
    explicit LoadDataTest(QObject *parent = nullptr);

private Q_SLOTS:
    void testLoadRouteFromGpx();
    void testLoadRouteFromPolyline();

private:
    MainWindow window;
};

#endif // LOADDATATEST_H
