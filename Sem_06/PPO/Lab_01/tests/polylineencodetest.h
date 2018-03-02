#pragma once

#include <QTest>

#include <polylineencoder.h>

class PolylineEncodeTest : public QObject
{
    Q_OBJECT

private:
    void test(PolylineEncoder &encoder, const QString &expected);

private Q_SLOTS:
    void test_1();
    void test_2();
    void test_3();
    void test_4();
};
