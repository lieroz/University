#include <common/route.h>

#include <QVector>

Route::Route()
{

}

Route::Route(const QString &name, qint32 length, const QDateTime &date,
             const QVector<QPointF> &coords, QObject *parent)
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

void Route::setLength(qint32 length)
{
    m_length = length;
}

qint32 Route::getLength() const
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

void Route::appendCoordinate(const QPointF &coord)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.addPoint(coord);
}

void Route::appendCoordinates(const QVector<QPointF> &coords)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.addPoints(coords);
}

void Route::insertCoordinate(qint32 index, const QPointF &coord)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.insertPoint(index, coord);
}

void Route::insertCoordinates(qint32 index, const QVector<QPointF> &coords)
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

void Route::replaceCoordinate(qint32 index, const QPointF &coord)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.replacePoint(index, coord);
}

void Route::replaceCoordinates(qint32 index, const QVector<QPointF> &coords)
{
    QWriteLocker guard(&m_rwlock);
    m_encoder.replacePoints(index, coords);
}

const QVector<QPointF> &Route::getCoordinates()
{
    QReadLocker guard(&m_rwlock);
    return m_encoder.polyline();
}

QString Route::getPolyline()
{
    QReadLocker guard(&m_rwlock);
    return m_encoder.encode();
}
