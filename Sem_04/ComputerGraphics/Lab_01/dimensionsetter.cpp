#include "dimensionsetter.hpp"
#include <QDebug>

DimensionSetter::DimensionSetter(QGraphicsScene* scene, const QVector<QPoint>& first_set,
                                 const QVector<QPoint>& second_set) {
    this->scene = scene;
    this->first_set = first_set;
    this->second_set = second_set;
    this->setUpDimension();
}

void DimensionSetter::setUpDimension() {
    const QVector<QPoint> set = first_set + second_set;
    QPoint min = set.at(0);
    QPoint max = set.at(0);

    foreach (QPoint point, first_set + second_set) {
        min.setX(point.x() < min.x() ? point.x() : min.x());
        min.setY(point.y() < min.y() ? point.y() : min.y());
        max.setX(point.x() > max.x() ? point.x() : max.x());
        max.setX(point.y() > max.y() ? point.y() : max.y());
    }

    foreach (QPoint point, first_set) {
        point.setX(point.x() + min.x());
        point.setY(point.y() + min.y());

        qDebug() << point;
    }

    foreach (QPoint point, second_set) {
        point.setX(point.x() + min.x());
        point.setY(point.y() + min.y());

        qDebug() << point;
    }
}
