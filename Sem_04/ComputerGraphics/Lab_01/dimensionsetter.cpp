#include "dimensionsetter.hpp"

void DimensionSetter::setUpDimension(QGraphicsScene* scene, QVector<Point2D>& first_set, QVector<Point2D>& second_set) {
    const QVector<Point2D> set = first_set + second_set;

    if (set.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Пустое множество");
        return;
    }

    Point2D min = set.at(0);
    Point2D max = set.at(0);

    for (auto& point : set) {
        min.x = point.x < min.x ? point.x : min.x;
        min.y = point.y < min.y ? point.y : min.y;
        max.x = point.x > max.x ? point.x : max.x;
        max.y = point.y > max.y ? point.y : max.y;
    }

    const double dimension_ratio = qMin(static_cast<double>(scene->width()) / (max.x - min.x),
                                        static_cast<double>(scene->height()) / (max.y - min.y));

    auto normalization = [&scene, &dimension_ratio, &min](QVector<Point2D>& vector) {
        for (auto& point : vector) {
            point.x = (point.x - min.x) * dimension_ratio;
            point.y = scene->height() - (point.y - min.y) * dimension_ratio;
        }
    };

    normalization(first_set);
    normalization(second_set);
}
