#pragma once

#include <QObject>
#include <QDateTime>
#include <QReadWriteLock>

#include <polylineencoder.h>

class Route : public QObject
{
public:
    Route();
    Route(const QString &name, qreal length, const QDateTime &date,
          const QVector<QGeoCoordinate> &coords, QObject *parent = Q_NULLPTR);
    Route(const Route&);
    ~Route();

    Route &operator=(const Route &route);

    void setName(const QString &name);
    const QString &getName() const;

    void setLength(qreal length);
    qreal getLength() const;

    void setDate(const QDateTime &date);
    const QDateTime &getDate() const;

    void appendCoordinate(const QGeoCoordinate &coord);
    void appendCoordinates(const QVector<QGeoCoordinate> &coords);

    void insertCoordinate(qint32 index, const QGeoCoordinate &coord);
    void insertCoordinates(qint32 index, const QVector<QGeoCoordinate> &coords);

    void removeCoordinate(qint32 index);
    void removeCoordinates(qint32 index, qint32 n);

    void replaceCoordinate(qint32 index, const QGeoCoordinate &coord);
    void replaceCoordinates(qint32 index, const QVector<QGeoCoordinate> &coords);

    const QVector<QGeoCoordinate> &getCoordinates();
    QString getPolyline();

private:
    QString m_name;
    qreal m_length;
    QDateTime m_date;
    PolylineEncoder m_encoder;
    QReadWriteLock m_rwlock;
};
