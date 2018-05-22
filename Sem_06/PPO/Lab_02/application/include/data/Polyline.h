//
// Created by lieroz on 10.05.18.
//

#ifndef LAB_02_POLYLINE_H
#define LAB_02_POLYLINE_H

#include <data/models/Route.h>

namespace Polyline
{
    QString encode(QSharedPointer<Route> route);
    QSharedPointer<Route> decode(const QString &polyline);
} //Polyline

#endif //LAB_02_POLYLINE_H
