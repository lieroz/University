#ifndef POINT2D_HPP
#define POINT2D_HPP

struct Point2D {
    double x;
    double y;

    explicit Point2D() = default;
    explicit Point2D(double x, double y) : x{x}, y{y} {}
    virtual ~Point2D() = default;
};

#endif // POINT2D_HPP
