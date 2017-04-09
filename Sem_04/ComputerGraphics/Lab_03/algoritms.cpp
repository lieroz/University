#include "algoritms.hpp"

void Algorithms::standard(QGraphicsScene* graphics_scene, QPixmap* pixmap, QLineF line, QColor color) {
    QPainter painter(pixmap);
    painter.setPen(QPen(color));
    painter.drawLine(line);
    graphics_scene->addPixmap(*pixmap);
}

void Algorithms::cda(QGraphicsScene* graphics_scene, QPixmap* pixmap, QLineF line, QColor color) {
    QPainter painter(pixmap);
    painter.setPen(QPen(color));
    QPointF curr = line.p1();

    if (curr == line.p2()) {
        painter.drawPoint(curr);

    } else {
        double dx = line.p2().x() - line.p1().x();
        double dy = line.p2().y() - line.p1().y();
        int l = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

        dx /= l;
        dy /= l;

        for (int i = 0; i < l; ++i) {
            painter.drawPoint(curr);
            curr.setX(curr.x() + dx);
            curr.setY(curr.y() + dy);
        }

        graphics_scene->addPixmap(*pixmap);
    }
}

void Algorithms::brezenham_int(QGraphicsScene* graphics_scene, QPixmap* pixmap, QLineF line, QColor color) {
    QPainter painter(pixmap);
    painter.setPen(QPen(color));
    QPointF curr = line.p1();

    if (curr == line.p2()) {
        painter.drawPoint(curr);

    } else {
        int dx = (line.p2().x() - line.p1().x());
        int dy = (line.p2().y() - line.p1().y());
        int sx = dx > 0 ? 1 : -1;
        int sy = dy > 0 ? 1 : -1;

        dx = abs(dx);
        dy = abs(dy);

        int sw = dx > dy ? 0 : 1;
        sw == 1 ? std::swap(dx, dy) : void();
        int e = 2 * dy - dx;

        for (int i = 0; i < dx; ++i) {
            painter.drawPoint(curr);

            if (e >= 0) {
                !sw ? curr.setY(curr.y() + sy) : curr.setX(curr.x() + sx);
                e -= 2 * dx;
            }

            !sw ? curr.setX(curr.x() + sx) : curr.setY(curr.y() + sy);
            e += 2 * dy;
        }

        graphics_scene->addPixmap(*pixmap);
    }
}

void Algorithms::brezenham_double(QGraphicsScene* graphics_scene, QPixmap* pixmap, QLineF line, QColor color) {
    QPainter painter(pixmap);
    painter.setPen(QPen(color));
    QPointF curr = line.p1();

    if (curr == line.p2()) {
        painter.drawPoint(curr);

    } else {
        int dx = (line.p2().x() - line.p1().x());
        int dy = (line.p2().y() - line.p1().y());
        int sx = dx > 0 ? 1 : -1;
        int sy = dy > 0 ? 1 : -1;

        dx = abs(dx);
        dy = abs(dy);

        int sw = dx > dy ? 0 : 1;
        sw == 1 ? std::swap(dx, dy) : void();
        double m = (dy + 0.0) / dx;
        double e = m - 0.5;

        for (int i = 0; i < dx; ++i) {
            painter.drawPoint(curr);

            if (e >= 0) {
                !sw ? curr.setY(curr.y() + sy) : curr.setX(curr.x() + sx);
                --e;
            }

            !sw ? curr.setX(curr.x() + sx) : curr.setY(curr.y() + sy);
            e += m;
        }

        graphics_scene->addPixmap(*pixmap);
    }
}

void Algorithms::draw_point(QPointF point, QPen pen, QPixmap* pixmap, double br) {
    QPainter painter(pixmap);
    int r, g, b, a;

    pen.color().getRgb(&r, &g, &b, &a);

    r += (a - r) - (a - r) * br;
    g += (a - g) - (a - g) * br;
    b += (a - b) - (a - b) * br;

    pen.setColor(QColor(r, g, b, a));
    painter.setPen(pen);
    painter.drawPoint(point);
}

void Algorithms::brezenham_gradation(QGraphicsScene* graphics_scene, QPixmap* pixmap, QLineF line, QColor color) {
    int i_max = 256;
    QPen pen(color);

    if (line.p2() == line.p1()) {
        Algorithms::draw_point(line.p2(), pen, pixmap, 1);

    } else {
        int curr_x = line.p1().x();
        int curr_y = line.p1().y();
        int dx = (line.p2().x() - line.p1().x());
        int dy = (line.p2().y() - line.p1().y());
        int sx = dx > 0 ? 1 : -1;
        int sy = dy > 0 ? 1 : -1;

        dx = abs(dx);
        dy = abs(dy);

        int sw = dx > dy ? 0 : 1;
        sw == 1 ? std::swap(dx, dy) : void();
        double m = static_cast<double>(dy) / dx * i_max;
        double e = i_max / 2;
        double w = i_max - m;

        Algorithms::draw_point(QPointF(curr_x, curr_y), pen, pixmap, e / i_max);

        for (int i = 0; i < dx; ++i) {

            if (e < w) {
                sw == 0 ? curr_x += sx : curr_y += sy;
                e += m;

            } else {
                curr_x += sx;
                curr_y += sy;
                e -= w;
            }

            Algorithms::draw_point(QPointF(curr_x, curr_y), pen, pixmap, e / i_max);
        }

        graphics_scene->addPixmap(*pixmap);
    }
}
