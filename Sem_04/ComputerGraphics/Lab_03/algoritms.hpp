#ifndef LINEALGORITMS_HPP
#define LINEALGORITMS_HPP

#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QLineF>
#include <QColor>

class Algorithms {
    public:
        enum algorithm {
            STANDARD, CDA, BREZENHAM_INT, BREZENHAM_DOUBLE, BREZENHAM_GRADATION
        };

        Algorithms() = delete;
        Algorithms(const Algorithms&) = delete;
        ~Algorithms() = delete;

        Algorithms& operator=(const Algorithms&) = delete;

        static void standard(QGraphicsScene*, QPixmap*, QLineF, QColor);
        static void cda(QGraphicsScene*, QPixmap*, QLineF, QColor);
        static void brezenham_int(QGraphicsScene*, QPixmap*, QLineF, QColor);
        static void brezenham_double(QGraphicsScene*, QPixmap*, QLineF, QColor);
        static void brezenham_gradation(QGraphicsScene*, QPixmap*, QLineF, QColor);

    private:
        static void draw_point(QPointF, QPen, QPixmap*, double);
};

#endif // LINEALGORITMS_HPP
