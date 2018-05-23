//
// Created by lieroz on 22.05.18.
//

#include <PolylineTest.h>

PolylineTest::PolylineTest(QObject *parent)
    : QObject(parent)
{
}

void PolylineTest::testDecode(QSharedPointer<Route> route, const QString &polyline)
{
    auto result = Polyline::decode(polyline);
    for (auto i = 0; i < result->getPath().count(); ++i) {
        QCOMPARE(*result->getCoordinate(i), *route->getCoordinate(i));
    }
}

void PolylineTest::testEncode(QSharedPointer<Route> route, const QString &expected)
{
    auto result = Polyline::encode(route);
    QCOMPARE(expected, result);
}

void PolylineTest::testDecode_1()
{
    Route route;
    route.addCoordinate({0, 0});
    testDecode(QSharedPointer<Route>::create(route), "??");
}

void PolylineTest::testDecode_2()
{
    Route route;
    route.addCoordinate({-90.0, -180.0});
    route.addCoordinate({0, 0});
    route.addCoordinate({90.0, 180.0});
    testDecode(QSharedPointer<Route>::create(route), "~bidP~fsia@_cidP_gsia@_cidP_gsia@");
}

void PolylineTest::testDecode_3()
{
    Route route;
    testDecode(QSharedPointer<Route>::create(route), "");
}

void PolylineTest::testDecode_4()
{
    Route route;
    route.addCoordinate({38.5, -120.2});
    route.addCoordinate({40.7, -120.95});
    route.addCoordinate({43.252, -126.453});
    testDecode(QSharedPointer<Route>::create(route), "_p~iF~ps|U_ulLnnqC_mqNvxq`@");
}

void PolylineTest::testEncode_1()
{
    Route route;
    route.addCoordinate({0, 0});
    testEncode(QSharedPointer<Route>::create(route), "??");
}

void PolylineTest::testEncode_2()
{
    Route route;
    route.addCoordinate({-90.0, -180.0});
    route.addCoordinate({0, 0});
    route.addCoordinate({90.0, 180.0});
    testEncode(QSharedPointer<Route>::create(route), "~bidP~fsia@_cidP_gsia@_cidP_gsia@");
}

void PolylineTest::testEncode_3()
{
    Route route;
    testEncode(QSharedPointer<Route>::create(route), "");
}

void PolylineTest::testEncode_4()
{
    Route route;
    route.addCoordinate({38.5, -120.2});
    route.addCoordinate({40.7, -120.95});
    route.addCoordinate({43.252, -126.453});
    testEncode(QSharedPointer<Route>::create(route), "_p~iF~ps|U_ulLnnqC_mqNvxq`@");
}

QTEST_GUILESS_MAIN(PolylineTest)
#include "PolylineTest.moc"
