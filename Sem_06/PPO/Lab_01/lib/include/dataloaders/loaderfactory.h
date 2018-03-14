#pragma once

#include <QObject>
#include <QMap>
#include <functional>

#include <dataloaders/dataloaders.h>

typedef std::function<void (const QString &, Route &)> LoaderFunc;
extern QMap<QString, LoaderFunc> registeredFileTypes;

class LoaderFactory : public QObject
{
public:
    static LoaderFunc getDataloader(const QString &fileType);
};
