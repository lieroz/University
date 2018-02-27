#pragma once

#include <QObject>
#include <QMap>
#include <functional>

#include <dataloaders/dataloaders.h>

extern QMap<QString, std::function<AbstractDataLoader *(const QString &)>> registeredFileTypes;

class LoaderFactory : public QObject
{
public:
    static std::function<AbstractDataLoader *(const QString &)> createDataloader(const QString &fileType);
};
