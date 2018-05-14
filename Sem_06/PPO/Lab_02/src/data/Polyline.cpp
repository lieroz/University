//
// Created by lieroz on 10.05.18.
//

#include <data/Polyline.h>

static const qreal s_presision = 100000.0;
static const quint32 s_chunkSize = 5;
static const quint32 s_asciiOffset = 63;
static const quint32 s_5bitMask = 0x1f;
static const quint32 s_6bitMask = 0x20;

void encodeValue(QString &str, double value)
{
    auto e5 = static_cast<quint32>(qRound(value * s_presision));
    e5 <<= 1;
    if (value < 0) {
        e5 = ~e5;
    }

    bool hasNextChunk;
    do {
        quint32 nextChunk = (e5 >> s_chunkSize);
        hasNextChunk = nextChunk > 0;

        quint32 charVar = e5 & s_5bitMask;
        if (hasNextChunk) {
            charVar |= s_6bitMask;
        }
        charVar += s_asciiOffset;
        str += (char) charVar;

        e5 = nextChunk;
    } while (hasNextChunk);
}

double decodeValue(const QString &polyline, quint32 i)
{
    quint32 result = 0;
    quint32 shift = 0;
    uchar c = 0;
    do {
        c = static_cast<uchar>(polyline.at(i++).toLatin1());
        c -= s_asciiOffset;
        result |= (c & s_5bitMask) << shift;
        shift += s_chunkSize;
    } while (c >= s_6bitMask);

    if (result & static_cast<quint32>(1)) {
        result = ~result;
    }
    result >>= 1;
    return result / s_presision;
}

namespace Polyline
{
    QString encode(QSharedPointer<Route> route)
    {
        QString result;
        double latPrev = .0;
        double lonPrev = .0;

        for (auto &coordinate : route->getPath()) {
            const auto lat = coordinate.getLatitude();
            const auto lon = coordinate.getLongitude();

            encodeValue(result, lat - latPrev);
            encodeValue(result, lon - lonPrev);

            latPrev = lat;
            lonPrev = lon;
        }

        return result;
    }

    QSharedPointer<Route> decode(const QString &polyline)
    {
        Route route;
        unsigned int i = 0;
        while (i < polyline.size()) {
            auto lat = decodeValue(polyline, i);
            auto lon = decodeValue(polyline, i);

            if (!route.getPath().isEmpty()) {
                const auto &prevPoint = route.getPath().back();
                lat += prevPoint.getLatitude();
                lon += prevPoint.getLongitude();
            }
            route.addCoordinate({lat, lon, 0});
        }

        return QSharedPointer<Route>::create(route);
    }
} //Polyline
