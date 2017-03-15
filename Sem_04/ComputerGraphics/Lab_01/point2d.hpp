#ifndef POINT2D_HPP
#define POINT2D_HPP

#include <QtMath>

struct Point2D {
    double x;
    double y;

    explicit Point2D() = default;
    explicit Point2D(const double x, const double y) : x{x}, y{y} {}
    virtual ~Point2D() = default;

    friend bool operator==(const Point2D& lhs, const Point2D& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

#endif // POINT2D_HPP
