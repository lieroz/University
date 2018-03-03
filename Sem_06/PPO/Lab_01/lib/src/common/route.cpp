#include <common/route.h>

Route::Route()
{
    m_length = 0;
    m_date = QDateTime::currentDateTime();
}

Route::Route(const QString &name, qreal length,
             const QDateTime &date, const QGeoPath &coords)
{
    m_name = name;
    m_length = length;
    m_date = date;
    m_encoder.addPoints(coords);
}

Route::Route(const Route &route)
{
    m_name = route.m_name;
    m_length = route.m_length;
    m_date = route.m_date;
    m_encoder.addPoints(route.m_encoder.polyline());
}

Route &Route::operator=(const Route &route)
{
    m_name = route.m_name;
    m_length = route.m_length;
    m_date = route.m_date;
    m_encoder = route.m_encoder;
    return *this;
}

void Route::setName(const QString &name)
{
    m_name = name;
}

QString Route::getName()
{
    return m_name;
}

void Route::setLength(qreal length)
{
    m_length = length;
}

void Route::updateLength()
{
    QReadLocker guard(&m_rwlock);
    m_length = 0;

    for (auto i = 0; i < m_encoder.polyline().size() - 1; ++i) {
        const auto first =  m_encoder.polyline().coordinateAt(i);
        const auto second = m_encoder.polyline().coordinateAt(i + 1);
        m_length += first.distanceTo(second);
    }
}

qreal Route::getLength()
{
    return m_length;
}

void Route::setDate(const QDateTime &date)
{
    m_date = date;
}

QDateTime Route::getDate()
{
    return m_date;
}

void Route::appendCoordinate(const QGeoCoordinate &coord)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.addPoint(coord);
}

void Route::appendCoordinates(const QGeoPath &coords)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.addPoints(coords);
}

void Route::insertCoordinate(qint32 index, const QGeoCoordinate &coord)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.insertPoint(index, coord);
}

void Route::insertCoordinates(qint32 index, const QGeoPath &coords)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.insertPoints(index, coords);
}

void Route::removeCoordinate(qint32 index)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.removePoint(index);
}

void Route::removeCoordinates(qint32 index, qint32 n)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.removePoints(index, n);
}

void Route::replaceCoordinate(qint32 index, const QGeoCoordinate &coord)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.replacePoint(index, coord);
}

void Route::replaceCoordinates(qint32 index, const QGeoPath &coords)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.replacePoints(index, coords);
}

QGeoPath Route::getCoordinates()
{
    QReadLocker guard(&m_rwlock);
    return m_encoder.polyline();
}

QString Route::getPolyline()
{
    QReadLocker guard(&m_rwlock);
    return m_encoder.encode();
}
