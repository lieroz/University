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

        void setUpDimension(QGraphicsScene*, QVector<Point2D>&, QVector<Point2D>&);
        void normalize(QGraphicsScene*, QVector<Point2D>&);

    private:
        double dimension_ratio;
        Point2D min;
        Point2D max;
};

#endif // DIMENSIONSETTER_HPP
