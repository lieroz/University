#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QMessageBox>
#include <QVector>
#include <QPoint>
#include <QtMath>

#include "drawer.hpp"

class Solver {
    public:
        explicit Solver() = default;
        virtual ~Solver() = default;

        static const QVector<QVector<QPoint>> solve(const QVector<QPoint>&, const QVector<QPoint>&);

    private:
        static const QVector<QVector<QPoint>> defineTriangles(const QVector<QPoint>&);
        static const QPoint defineAltitudesIntersectionPoint(const QPoint&, const QPoint&, const QPoint&);
};

#endif // SOLVER_HPP
