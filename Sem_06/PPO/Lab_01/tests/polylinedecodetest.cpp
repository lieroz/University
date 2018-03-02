#include <polylinedecodetest.h>

void PolylineDecodeTest::test(QGeoPath &geoPath, const QString &polyline)
{
    QGeoPath result = PolylineEncoder::decode(polyline);

    for (auto i = 0; i < result.size(); ++i) {
        QCOMPARE(geoPath.coordinateAt(i), result.coordinateAt(i));
    }
}

void PolylineDecodeTest::test_1()
{
    QGeoPath geoPath;
    geoPath.addCoordinate(QGeoCoordinate(.0, .0));

    test(geoPath, "??");
}

void PolylineDecodeTest::test_2()
{
    QGeoPath geoPath;
    geoPath.addCoordinate(QGeoCoordinate(-90.0, -180.0));
    geoPath.addCoordinate(QGeoCoordinate(.0, .0));
    geoPath.addCoordinate(QGeoCoordinate(90.0, 180.0));

    test(geoPath, "~bidP~fsia@_cidP_gsia@_cidP_gsia@");
}

void PolylineDecodeTest::test_3()
{
    // Empty list of points.
    QGeoPath geoPath;

    return test(geoPath, QString());
}

void PolylineDecodeTest::test_4()
{
    // Coordinates from https://developers.google.com/maps/documentation/utilities/polylinealgorithm
    QGeoPath geoPath;
    geoPath.addCoordinate(QGeoCoordinate(38.5, -120.2));
    geoPath.addCoordinate(QGeoCoordinate(40.7, -120.95));
    geoPath.addCoordinate(QGeoCoordinate(43.252, -126.453));

    return test(geoPath, "_p~iF~ps|U_ulLnnqC_mqNvxq`@");
}

QTEST_MAIN(PolylineDecodeTest)
#include "polylinedecodetest.moc"
