#include "drawer.hpp"

void Drawer::drawSetPoints(QGraphicsScene* scene, const QVector<Point2D>& points, const QColor& color) {
    for (auto& point : points) {
        scene->addEllipse(point.x - size, point.y - size, size * 2, size * 2, QPen{color}, QBrush{color});
    }
}

void Drawer::drawPoints(QGraphicsScene* scene, const QVector<Point2D>& first_set, const QVector<Point2D>& second_set) {
    Drawer::drawSetPoints(scene, first_set, Qt::red);
    Drawer::drawSetPoints(scene, second_set, Qt::blue);
}

void Drawer::drawLine(QGraphicsScene* scene, const Point2D& A, const Point2D& B, const QColor& color) {
    QPen pen = QPen{color};
    pen.setWidth(3);
    scene->addLine(A.x, A.y, B.x, B.y, pen);
}

void Drawer::drawHeights(QGraphicsScene* scene, const QVector<Point2D>& points, const QColor& color) {
    for (int i{}; i < points.size() - 1; ++i) {
        scene->addLine(points.at(3).x, points.at(3).y, points.at(i).x, points.at(i).y, QPen{color});
    }
}

void Drawer::drawText(QGraphicsScene* scene, const QVector<Point2D>& points) {
    for (int i{}; i < points.size() - 1; ++i) {
        QGraphicsTextItem* text = scene->addText(QString::number(i + 1));
        text->setPos(points[i].x, points[i].y - 2);
    }
}

void Drawer::drawTriangle(QGraphicsScene* scene, const QVector<Point2D>& points, const QColor& color) {
    for (int i{}; i < points.size() - 2; ++i) {

        for (int j{i + 1}; j < points.size() - 1; ++j) {
            Drawer::drawLine(scene, points[i], points[j], color);
        }
    }

    Drawer::drawText(scene, points);
}

void Drawer::drawAnswer(QGraphicsScene* scene, const QVector<Point2D>& first, const QVector<Point2D>& second) {
    Drawer::drawHeights(scene, first, Qt::darkYellow);
    Drawer::drawHeights(scene, second, Qt::darkYellow);
    Drawer::drawLine(scene, first[3], second[3], Qt::darkGreen);
    Drawer::drawTriangle(scene, first, Qt::darkGray);
    Drawer::drawTriangle(scene, second, Qt::darkGray);
}
