//
// Created by lieroz on 10.05.18.
//

#ifndef LAB_02_ROUTE_H
#define LAB_02_ROUTE_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QSharedPointer>

#include <data/models/Coordinate.h>

class Route
{
public:
    Route();
    Route(const Route &other);
    Route(Route &&other);
    ~Route() = default;

    Route(const QString &name, const QVector<Coordinate> &path);

    Route &operator=(const Route &other);
    Route &operator=(Route &&other) noexcept;

    const QString &getName();
    qreal getLength();
    const QDateTime &getCreated();
    const QVector<Coordinate> &getPath();

    void setName(const QString &name);
    void setPath(const QVector<Coordinate> &path);

    bool addCoordinate(qint32 index, const Coordinate &coordinate);
    void addCoordinate(const Coordinate &coordinate);
    bool removeCoordinate(qint32 index);
    void removeCoordinate();
    bool updateCoordinate(qint32 index, const Coordinate &coordinate);
    QSharedPointer<Coordinate> getCoordinate(qint32 index);

private:
    void updateLength();

    QString m_name;
    qreal m_length;
    QDateTime m_created;
    QVector<Coordinate> m_path;
};

#endif //LAB_02_ROUTE_H
