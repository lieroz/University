#include "solver.hpp"
#include <QtMath>
#include <QDebug>

void Solver::solve(const QVector<QPoint>& first_set, const QVector<QPoint>& second_set) {
    if (first_set.size() < 3 || second_set.size() < 3) {
        QMessageBox::warning(nullptr, "Ошибка", "На одном из 2-ух множеств нет треугольников!");
        return;
    }

    const QVector<QVector<QPoint>> first_set_triangles = Solver::defineTriangles(first_set);
    const QVector<QVector<QPoint>> second_set_triangles = Solver::defineTriangles(second_set);

    double minimal_angle = 90;

    for (auto& first : first_set_triangles) {

        for (auto& second : second_set_triangles) {
            const double angle = qRadiansToDegrees(qAtan(static_cast<double>(qAbs(first.at(3).y() - second.at(3).y()))
                                                         / static_cast<double>(qAbs(first.at(3).x() - second.at(3).x()))));
            minimal_angle = angle < minimal_angle ? angle : minimal_angle;
        }
    }

    qDebug() << minimal_angle;
}


const QVector<QVector<QPoint>> Solver::defineTriangles(const QVector<QPoint>& points) {
    QVector<QVector<QPoint>> triangles;

    for (int i{}; i < points.size() - 2; ++i) {

        for (int j{i + 1}; j < points.size() - 1; ++j) {

            for (int k{j + 1}; k < points.size(); ++k) {
                triangles.append({points.at(i), points.at(j), points.at(k),
                                  defineAltitudesIntersectionPoint(points.at(i), points.at(j), points.at(k))});
            }
        }
    }

    return triangles;
}

const QPoint Solver::defineAltitudesIntersectionPoint(const QPoint& A, const QPoint& B, const QPoint& C) {
    const double a1 = B.x() - A.x();
    const double b1 = A.y() - B.y();
    const double c1 = a1 * C.x() - b1 * C.y();

    const double a2 = C.x() - A.x();
    const double b2 = A.y() - C.y();
    const double c2 = a2 * B.x() - b2 * B.y();

    const int x = static_cast<int>(b1 != 0 ? qRound((c1 * b2 / b1 - c2) / (a2 - a1 * b2 / b1)) :
                                             qRound((c1 * b1 / b2 - c1) / (a1 - a2 * b1 / b2)));
    const int y = static_cast<int>(b1 != 0 ? qRound(-(a1 * x + c1) / b1) :
                                             qRound(-(a2 * x + c2) / b2));

    return QPoint{-x, y};
}
