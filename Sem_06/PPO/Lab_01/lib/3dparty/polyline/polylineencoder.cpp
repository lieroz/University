/*
MIT License

Copyright (c) 2017 Vahan Aghajanyan <vahancho@gmail.com>
Copyright (c) 2018 Andrey Kamakin <a.kamakin@icloud.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "polylineencoder.h"

static const qreal  s_presision   = 100000.0;
static const qint32 s_chunkSize   = 5;
static const qint32 s_asciiOffset = 63;
static const qint32 s_5bitMask    = 0x1f; // 0b11111 = 31
static const qint32 s_6bitMask    = 0x20; // 0b100000 = 32

PolylineEncoder::PolylineEncoder()
{

}

PolylineEncoder::PolylineEncoder(const PolylineEncoder &encoder)
{
    QGeoPath tmp(encoder.m_geoPath);
    m_geoPath = tmp;
}

PolylineEncoder::~PolylineEncoder()
{

}

PolylineEncoder &PolylineEncoder::operator=(const PolylineEncoder &encoder)
{
    m_geoPath = encoder.m_geoPath;
}

void PolylineEncoder::addPoint(const QGeoCoordinate &geoCoord)
{
    Q_ASSERT(geoCoord.latitude() <= 90.0 && geoCoord.latitude() >= -90.0);
    Q_ASSERT(geoCoord.longitude() <= 180.0 && geoCoord.longitude() >= -180.0);

    m_geoPath.addCoordinate(geoCoord);
}

void PolylineEncoder::addPoints(const QGeoPath &geoPath)
{
    for (auto i = 0; i < geoPath.size(); ++i) {
        m_geoPath.addCoordinate(geoPath.coordinateAt(i));
    }
}

void PolylineEncoder::insertPoint(qint32 index, const QGeoCoordinate &geoCoord)
{
    Q_ASSERT(geoCoord.latitude() <= 90.0 && geoCoord.latitude() >= -90.0);
    Q_ASSERT(geoCoord.longitude() <= 180.0 && geoCoord.longitude() >= -180.0);

    m_geoPath.insertCoordinate(index, geoCoord);
}

void PolylineEncoder::insertPoints(qint32 index, const QGeoPath &geoPath)
{
    for (auto i = 0; i < geoPath.size(); ++i) {
        m_geoPath.insertCoordinate(index++, geoPath.coordinateAt(i));
    }
}

void PolylineEncoder::removePoint(qint32 index)
{
    m_geoPath.removeCoordinate(index);
}

void PolylineEncoder::removePoints(qint32 index, qint32 n)
{
    for (auto i = index; i < index + n; ++i) {
        removePoint(i);
    }
}

void PolylineEncoder::replacePoint(qint32 index, const QGeoCoordinate &geoCoord)
{
    Q_ASSERT(geoCoord.latitude() <= 90.0 && geoCoord.latitude() >= -90.0);
    Q_ASSERT(geoCoord.longitude() <= 180.0 && geoCoord.longitude() >= -180.0);

    m_geoPath.replaceCoordinate(index, geoCoord);
}

void PolylineEncoder::replacePoints(qint32 index, const QGeoPath &geoPath)
{
    for (auto i = index; i < index + geoPath.size(); ++i) {
        removePoint(i);
    }
}

QString PolylineEncoder::encode()
{
    return encode(m_geoPath);
}

QString PolylineEncoder::encode(qreal value)
{
    qint32 e5 = qRound(value * s_presision); // (2)

    e5 <<= 1;                                // (4)

    if (value < 0) {
        e5 = ~e5;                            // (5)
    }

    bool hasNextChunk = false;
    QString result;

    // Split the value into 5-bit chunks and convert each of them to integer
    do {
        qint32 nextChunk = (e5 >> s_chunkSize); // (6), (7) - start from the left 5 bits.
        hasNextChunk = nextChunk > 0;

        qint32 charVar = e5 & s_5bitMask;       // 5-bit mask (0b11111 == 31). Extract the left 5 bits.
        if (hasNextChunk) {
            charVar |= s_6bitMask;              // (8)
        }
        charVar += s_asciiOffset;               // (10)
        result += (uchar)charVar;               // (11)

        e5 = nextChunk;
    } while (hasNextChunk);

    return result;
}

QString PolylineEncoder::encode(const QGeoPath &geoPath)
{
    QString result;

    // The first segment: offset from (.0, .0)
    qreal latPrev = .0;
    qreal lonPrev = .0;

    for (auto i = 0; i < geoPath.size(); ++i) {
        const auto coord = geoPath.coordinateAt(i);
        const auto lat = coord.latitude();
        const auto lon = coord.longitude();

        // Offset from the previous point
        result.append(encode(lat - latPrev));
        result.append(encode(lon - lonPrev));

        latPrev = lat;
        lonPrev = lon;
    }

    return result;
}

qreal PolylineEncoder::decode(const QString &coords, size_t &i)
{
    Q_ASSERT(i < coords.size());

    qint32 result = 0;
    qint32 shift = 0;
    uchar c = 0;
    do {
        c = coords.at(i++).cell();
        c -= s_asciiOffset;      // (10)
        result |= (c & s_5bitMask) << shift;
        shift += s_chunkSize;    // (7)
    } while (c >= s_6bitMask);

    if (result & 1) {
        result = ~result;        // (5)
    }
    result >>= 1;                // (4)

    // Convert to decimal value.
    return result / s_presision; // (2)
}

QGeoPath PolylineEncoder::decode(const QString &coords)
{
    QGeoPath geoPath;

    size_t i = 0;
    while (i < coords.count()) {
        auto lat = decode(coords, i);
        auto lon = decode(coords, i);

        if (!geoPath.isEmpty()) {
            const auto prevPoint = geoPath.coordinateAt(geoPath.size() - 1);
            lat += prevPoint.latitude();
            lon += prevPoint.longitude();
        }
        geoPath.addCoordinate(QGeoCoordinate(lat, lon));
    }

    return geoPath;
}

QGeoPath PolylineEncoder::polyline() const
{
    return m_geoPath;
}

void PolylineEncoder::clear()
{
    m_geoPath.~QGeoPath();
}
