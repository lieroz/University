#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QMessageBox>
#include <QVector>
#include <QPoint>

#include "point2d.hpp"

class Solver {
    public:
        explicit Solver() = default;
        virtual ~Solver() = default;

        static const QVector<QVector<Point2D>> solve(const QVector<Point2D>&, const QVector<Point2D>&);

    private:
        static const QVector<QVector<Point2D>> defineTriangles(const QVector<Point2D>&);
        static const Point2D defineAltitudesIntersectionPoint(const Point2D&, const Point2D&, const Point2D&);
};

#endif // SOLVER_HPP
