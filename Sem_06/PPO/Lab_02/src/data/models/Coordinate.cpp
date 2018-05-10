//
// Created by lieroz on 10.05.18.
//

#include <QtCore/QtCore>

#include <data/models/Coordinate.h>

Coordinate::Coordinate()
        : m_latitude(0), m_longitude(0), m_altitude(0)
{
}

Coordinate::Coordinate(const Coordinate &other)
        : Coordinate(other.m_latitude, other.m_longitude, other.m_altitude)
{
}

Coordinate::Coordinate(Coordinate &&other)
        : m_latitude(other.m_latitude), m_longitude(other.m_longitude), m_altitude(other.m_altitude)
{
    other.m_latitude = 0;
    other.m_longitude = 0;
    other.m_altitude = 0;
}

Coordinate::Coordinate(qreal latitude, qreal longitude, qreal altitude)
        : m_latitude(latitude), m_longitude(longitude), m_altitude(altitude)
{
}

Coordinate &Coordinate::operator=(const Coordinate &other)
{
    if (this != &other) {
        m_latitude = other.m_latitude;
        m_longitude = other.m_longitude;
        m_altitude = other.m_altitude;
    }
    return *this;
}

Coordinate &Coordinate::operator=(Coordinate &&other)
{
    if (this != &other) {
        m_latitude = other.m_latitude;
        m_longitude = other.m_longitude;
        m_altitude = other.m_altitude;

        other.m_latitude = 0;
        other.m_longitude = 0;
        other.m_altitude = 0;
    }
    return *this;
}

qreal Coordinate::getLatitude() const
{
    return m_latitude;
}

qreal Coordinate::getLongitude() const
{
    return m_longitude;
}

qreal Coordinate::getAltitude() const
{
    return m_altitude;
}

void Coordinate::setLatitude(qreal latitude)
{
    m_latitude = latitude;
}

void Coordinate::setLongitude(qreal longitude)
{
    m_longitude = longitude;
}

void Coordinate::setAltitude(qreal altitude)
{
    m_altitude = altitude;
}

qreal Coordinate::distanceTo(const Coordinate &other)
{
    qreal phi1 = qDegreesToRadians(m_latitude);
    qreal phi2 = qDegreesToRadians(other.m_latitude);
    qreal deltaPhi = qDegreesToRadians(other.m_latitude - m_latitude);
    qreal deltaLambda = qDegreesToRadians(other.m_longitude - m_longitude);
    qreal a = qPow(qSin(deltaPhi / 2), 2) + qCos(phi1) * qCos(phi2) * qPow(qSin(deltaLambda / 2), 2);
    qreal c = 2 * qAtan2(qSqrt(a), qSqrt(1 - a));
    return R * c;
}