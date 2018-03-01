#pragma once

#include <QDateTime>
#include <QReadWriteLock>

#include <polylineencoder.h>

class Route
{
public:
    Route();
    Route(const QString &name, qreal length,
          const QDateTime &date, const QGeoPath &coords);
    Route(const Route &route);
    ~Route() = default;

    Route &operator=(const Route &route);

    void setName(const QString &name);
    QString getName();

    void setLength(qreal length);
    void updateLength();
    qreal getLength();

    void setDate(const QDateTime &date);
    QDateTime getDate();

    void appendCoordinate(const QGeoCoordinate &coord);
    void appendCoordinates(const QGeoPath &coords);

    void insertCoordinate(qint32 index, const QGeoCoordinate &coord);
    void insertCoordinates(qint32 index, const QGeoPath &coords);

    void removeCoordinate(qint32 index);
    void removeCoordinates(qint32 index, qint32 n);

    void replaceCoordinate(qint32 index, const QGeoCoordinate &coord);
    void replaceCoordinates(qint32 index, const QGeoPath &coords);

    QGeoPath getCoordinates();
    QString getPolyline();

private:
    QString m_name;
    qreal m_length;
    QDateTime m_date;
    PolylineEncoder m_encoder;
    QReadWriteLock m_rwlock;
};
