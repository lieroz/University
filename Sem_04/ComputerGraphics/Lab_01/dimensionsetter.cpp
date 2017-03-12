#include "dimensionsetter.hpp"

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

    const double dimension_ratio = qMin(static_cast<double>(scene->width()) / (max.x() - min.x()),
                                        static_cast<double>(scene->height()) / (max.y() - min.y()));

    auto normalization = [&scene, &dimension_ratio, &min](QVector<QPoint>& vector) {
        for (auto& point : vector) {
            point.setX((point.x() - min.x()) * dimension_ratio);
            point.setY(scene->height() - (point.y() - min.y()) * dimension_ratio);
        }
    };

    normalization(first_set);
    normalization(second_set);
}
