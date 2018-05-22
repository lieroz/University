//
// Created by lieroz on 22.05.18.
//

#ifndef COORDINATETEST_H
#define COORDINATETEST_H

#include <QTest>

#include <ui/MainWindow.h>

class CoordinateTest : public QObject
{
    Q_OBJECT
public:
    explicit CoordinateTest(QObject *parent = nullptr);

private Q_SLOTS:
    void initTestCase();
    void testAddCoordinate();
    void testUpdateCoordinate();
    void testRemoveCoordinate();
    void cleanUpTestCase();

private:
    MainWindow window;
};

#endif // COORDINATETEST_H
