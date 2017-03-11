#include "drawer.hpp"

void Drawer::drawSetPoints(QGraphicsScene* scene, const QVector<QPoint>& points) {
    for (auto& point : points) {
        scene->addEllipse(point.x(), point.y(), 4, 4, QPen{Qt::red}, QBrush{Qt::red});
    }
}
