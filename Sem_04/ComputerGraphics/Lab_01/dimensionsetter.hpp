#ifndef DIMENSIONSETTER_HPP
#define DIMENSIONSETTER_HPP

#include <QGraphicsView>
#include <QMessageBox>
#include <QVector>

#include "point2d.hpp"

class DimensionSetter {
    public:
        explicit DimensionSetter() = default;
        virtual ~DimensionSetter() = default;

        static void setUpDimension(QGraphicsScene*, QVector<Point2D>&, QVector<Point2D>&);
};

#endif // DIMENSIONSETTER_HPP
