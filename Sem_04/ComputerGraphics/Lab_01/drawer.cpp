#include "drawer.hpp"

void Drawer::drawSetPoints(QGraphicsScene* scene, const QVector<QPoint>& points, const QColor& color) {
    for (auto& point : points) {
        scene->addEllipse(point.x(), point.y(), 4, 4, QPen{color}, QBrush{color});
    }
}

void Drawer::draw(QGraphicsScene* scene, const QVector<QPoint>& first_set, const QVector<QPoint>& second_set) {
    Drawer::drawSetPoints(scene, first_set, Qt::red);
    Drawer::drawSetPoints(scene, second_set, Qt::blue);
}
