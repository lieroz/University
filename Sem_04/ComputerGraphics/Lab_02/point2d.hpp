#ifndef POINT2D_HPP
#define POINT2D_HPP

struct Point2D {
    qreal x;
    qreal y;

    explicit Point2D() = default;
    explicit Point2D(qreal x, qreal y) : x{x}, y{y} {}
    virtual ~Point2D() = default;
};

#endif // POINT2D_HPP
