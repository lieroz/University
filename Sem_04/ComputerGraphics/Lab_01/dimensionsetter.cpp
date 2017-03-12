#include "dimensionsetter.hpp"
#include <QDebug>

void DimensionSetter::setUpDimension(QGraphicsScene* scene, QVector<QPoint>& first_set, QVector<QPoint>& second_set) {
    const QVector<QPoint> set = first_set + second_set;

    if (set.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Пустое множество");
        return;
    }

    QPoint min = set.at(0);
    QPoint max = set.at(0);

    for (auto& point : set) {
        min.setX(point.x() < min.x() ? point.x() : min.x());
        min.setY(point.y() < min.y() ? point.y() : min.y());
        max.setX(point.x() > max.x() ? point.x() : max.x());
        max.setY(point.y() > max.y() ? point.y() : max.y());
    }

    const double x_dimension_ratio = static_cast<double>(scene->width()) / ((max.x() + offset) - (min.x() - offset));
    const double y_dimension_ratio = static_cast<double>(scene->height()) / ((max.y() + offset) - (min.y() - offset));

    auto normalization = [&scene, &x_dimension_ratio, &y_dimension_ratio, &min](QVector<QPoint>& vector) {
        for (auto& point : vector) {
            point.setX((point.x() - min.x()) * x_dimension_ratio);
            point.setY(scene->height() - (point.y() - min.y() + offset * 2) * y_dimension_ratio);
        }
    };

    normalization(first_set);
    normalization(second_set);
}
