#include <polylineencodetest.h>

void PolylineEncodeTest::test(PolylineEncoder &encoder, const QString &expected)
{
    auto res = encoder.encode();
    if (res == expected) {
        auto decodedPolyline = encoder.decode(res);
        const auto &polyline = encoder.polyline();
        QCOMPARE(decodedPolyline.size(), polyline.size());

        for (size_t i = 0; i < polyline.size(); ++i) {
            const auto p1 = polyline.coordinateAt(i);
            const auto p2 = decodedPolyline.coordinateAt(i);
            QCOMPARE(p1, p2);
        }
    }

    QCOMPARE(expected, res);
}

void PolylineEncodeTest::test_1()
{
    PolylineEncoder encoder;
    encoder.addPoint(QGeoCoordinate(.0, .0));

    test(encoder, "??");
}

void PolylineEncodeTest::test_2()
{
    PolylineEncoder encoder;

    // Poles and equator.
    encoder.addPoint(QGeoCoordinate(-90.0, -180.0));
    encoder.addPoint(QGeoCoordinate(.0, .0));
    encoder.addPoint(QGeoCoordinate(90.0, 180.0));

    return test(encoder, "~bidP~fsia@_cidP_gsia@_cidP_gsia@");
}

void PolylineEncodeTest::test_3()
{
    // Empty list of points.
    PolylineEncoder encoder;

    return test(encoder, QString());
}

void PolylineEncodeTest::test_4()
{
    // Coordinates from https://developers.google.com/maps/documentation/utilities/polylinealgorithm
    PolylineEncoder encoder;
    encoder.addPoint(QGeoCoordinate(38.5, -120.2));
    encoder.addPoint(QGeoCoordinate(40.7, -120.95));
    encoder.addPoint(QGeoCoordinate(43.252, -126.453));

    return test(encoder, "_p~iF~ps|U_ulLnnqC_mqNvxq`@");
}

QTEST_MAIN(PolylineEncodeTest)
#include "polylineencodetest.moc"
