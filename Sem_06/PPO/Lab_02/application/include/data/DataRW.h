//
// Created by lieroz on 10.05.18.
//

#ifndef LAB_02_DATARW_H
#define LAB_02_DATARW_H

#include <QFile>
#include <functional>

#include <data/models/Route.h>

typedef std::function<QSharedPointer<Route>(const QString &)> rFunc;
typedef std::function<bool(QFile &, QSharedPointer<Route>)> wFunc;

std::pair<rFunc, wFunc> getRWFunctions(const QString &fileType);

#endif //LAB_02_DATARW_H
