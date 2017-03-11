#ifndef DIMENSIONSETTER_HPP
#define DIMENSIONSETTER_HPP

#include <QGraphicsScene>
#include <QVector>
#include <QPoint>

class DimensionSetter {
    public:
        explicit DimensionSetter(QGraphicsScene*, const QVector<QPoint>&, const QVector<QPoint>&);
         virtual~DimensionSetter() = default;

        void setUpDimension();

        friend bool operator<(const QPoint&, const QPoint&);
        friend bool operator>(const QPoint&, const QPoint&);

    private:
        QGraphicsScene* scene;
        QVector<QPoint> first_set;
        QVector<QPoint> second_set;
};

#endif // DIMENSIONSETTER_HPP
