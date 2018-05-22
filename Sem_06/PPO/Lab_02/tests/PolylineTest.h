//
// Created by lieroz on 22.05.18.
//

#ifndef POLYLINETEST_H
#define POLYLINETEST_H

#include <QTest>

#include <data/Polyline.h>

class PolylineTest : public QObject
{
    Q_OBJECT
public:
    explicit PolylineTest(QObject *parent = nullptr);

private:
    void testDecode(QSharedPointer<Route> route, const QString &polyline);
    void testEncode(QSharedPointer<Route> route, const QString &expected);

private Q_SLOTS:
    void testDecode_1();
    void testDecode_2();
    void testDecode_3();
    void testDecode_4();

    void testEncode_1();
    void testEncode_2();
    void testEncode_3();
    void testEncode_4();
};

#endif // POLYLINETEST_H
