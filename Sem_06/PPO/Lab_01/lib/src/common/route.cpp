#include <common/route.h>

#include <QVector>

Route::Route()
{
    m_length = 0;
    m_date = QDateTime::currentDateTime();
}

Route::Route(const QString &name, qreal length, const QDateTime &date,
             const QGeoPath &coords, QObject *parent)
    : m_name(name), m_length(length), m_date(date), QObject(parent)
{
    m_encoder.addPoints(coords);
}

Route::Route(const Route &route)
{
    m_name = route.m_name;
    m_length = route.m_length;
    m_date = route.m_date;
    m_encoder = route.m_encoder;
}

Route::~Route()
{

}

Route &Route::operator=(const Route &route)
{

}

void Route::setName(const QString &name)
{
    m_name = name;
}

const QString &Route::getName() const
{
    return m_name;
}

void Route::setLength(qreal length)
{
    m_length = length;
}

qreal Route::getLength() const
{
    return m_length;
}

void Route::setDate(const QDateTime &date)
{
    m_date = date;
}

const QDateTime &Route::getDate() const
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

const QGeoPath &Route::getCoordinates()
{
    QReadLocker guard(&m_rwlock);
    return m_encoder.polyline();
}

QString Route::getPolyline()
{
    QReadLocker guard(&m_rwlock);
    return m_encoder.encode();
}
