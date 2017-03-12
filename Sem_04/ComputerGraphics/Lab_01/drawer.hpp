#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <QGraphicsScene>
#include <QVector>
#include <QPoint>

class Drawer {
    public:
        explicit Drawer() = default;
        virtual ~Drawer() = default;

        static void draw(QGraphicsScene*, const QVector<QPoint>&, const QVector<QPoint>&);

    private:
        static void drawSetPoints(QGraphicsScene*, const QVector<QPoint>&, const QColor&);
};

#endif // DRAWER_HPP
