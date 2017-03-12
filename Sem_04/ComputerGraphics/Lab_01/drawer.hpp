#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QVector>
#include <QPoint>

class Drawer {
    public:
        explicit Drawer() = default;
        virtual ~Drawer() = default;

        static void drawPoints(QGraphicsScene*, const QVector<QPoint>&, const QVector<QPoint>&);
        static void drawAnswer(QGraphicsScene*, const QVector<QPoint>&, const QVector<QPoint>&);

    private:
        static const int size = 3;

        static void drawSetPoints(QGraphicsScene*, const QVector<QPoint>&, const QColor&);
        static void drawText(QGraphicsScene*, const QVector<QPoint>&);
        static void drawLine(QGraphicsScene*, const QPoint&, const QPoint&, const QColor&);
        static void drawHeights(QGraphicsScene*, const QVector<QPoint>&, const QColor&);
        static void drawTriangle(QGraphicsScene*, const QVector<QPoint>&, const QColor&);
};

#endif // DRAWER_HPP
