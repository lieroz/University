//
// Created by lieroz on 10.05.18.
//

#ifndef LAB_02_COORDINATE_H
#define LAB_02_COORDINATE_H

#include <QTypeInfo>

class Coordinate
{
    const qint32 R = 6371;

public:
    Coordinate();
    Coordinate(const Coordinate &other);
    Coordinate(Coordinate &&other);
    ~Coordinate() = default;

    Coordinate(qreal latitude, qreal longitude);

    Coordinate &operator=(const Coordinate &other);
    Coordinate &operator=(Coordinate &&other) noexcept;

    friend bool operator==(const Coordinate &lhs, const Coordinate &rhs);
    friend bool operator!=(const Coordinate &lhs, const Coordinate &rhs);

    qreal getLatitude() const;
    qreal getLongitude() const;
    qreal getAltitude() const;
    qreal getCourse() const;

    void setLatitude(qreal latitude);
    void setLongitude(qreal longitude);
    void setAltitude(qreal altitude);
    void setCourse(qreal course);

    qreal distanceTo(const Coordinate &other);

private:
    qreal m_latitude;
    qreal m_longitude;
    qreal m_altitude;
    qreal m_course;
};

#endif //LAB_02_COORDINATE_H
