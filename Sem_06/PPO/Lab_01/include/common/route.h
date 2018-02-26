#pragma once

#include <QObject>
#include <QDateTime>

#include <polyline/polylineencoder.h>

class Route : public QObject
{
public:
    Route();
    Route(const QString &name, qint32 length, const QDateTime &date,
          const QVector<QPointF> &coords, QObject *parent = Q_NULLPTR);
    Route(const Route&);
    ~Route();

    Route &operator=(const Route &route);

    void setName(const QString &name);
    const QString &getName() const;

    void setLength(qint32 length);
    qint32 getLength() const;

    void setDate(const QDateTime &date);
    const QDateTime &getDate() const;

    void appendCoordinate(const QPointF &coord);
    void appendCoordinates(const QVector<QPointF> &coords);

    void insertCoordinate(qint32 index, const QPointF &coord);
    void insertCoordinates(qint32 index, const QVector<QPointF> &coords);

    void removeCoordinate(qint32 index);
    void removeCoordinates(qint32 index, qint32 n);

    void replaceCoordinate(qint32 index, const QPointF &coord);
    void replaceCoordinates(qint32 index, const QVector<QPointF> &coords);

    const QVector<QPointF> &getCoordinates();
    QString getPolyline();

private:
    QString m_name;
    qint32 m_length;
    QDateTime m_date;
    PolylineEncoder m_encoder;
};
