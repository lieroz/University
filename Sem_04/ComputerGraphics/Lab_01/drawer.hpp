#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QVector>

#include "point2d.hpp"

class Drawer {
    public:
        explicit Drawer() = default;
        virtual ~Drawer() = default;

        static void drawPoints(QGraphicsScene*, const QVector<Point2D>&, const QVector<Point2D>&);
        static void drawAnswer(QGraphicsScene*, const QVector<Point2D>&, const QVector<Point2D>&);

    private:
        static const int size = 3;

        static void drawSetPoints(QGraphicsScene*, const QVector<Point2D>&, const QColor&);
        static void drawText(QGraphicsScene*, const QVector<Point2D>&);
        static void drawLine(QGraphicsScene*, const Point2D&, const Point2D&, const QColor&);
        static void drawHeights(QGraphicsScene*, const QVector<Point2D>&, const QColor&);
        static void drawTriangle(QGraphicsScene*, const QVector<Point2D>&, const QColor&);
};

#endif // DRAWER_HPP
