#ifndef OBJECTWRAPPER_HPP
#define OBJECTWRAPPER_HPP

#include <QColor>
#include <QLineF>
#include <QVector>

#include "algoritms.hpp"

struct LineWrapper {
    QLineF __line;
    QColor __color;
    Algorithms::algorithm __algorithm;

    LineWrapper() = default;
    LineWrapper(QLineF line, QColor color, Algorithms::algorithm algorithm)
        : __line(line), __color(color), __algorithm(algorithm) {
    }
};

#endif // OBJECTWRAPPER_HPP
