#pragma once

#include <QTest>

#include <polylineencoder.h>

class PolylineDecodeTest : public QObject
{
    Q_OBJECT

private:
    void test(QGeoPath &geoPath, const QString &polyline);

private Q_SLOTS:
    void test_1();
    void test_2();
    void test_3();
    void test_4();
};
