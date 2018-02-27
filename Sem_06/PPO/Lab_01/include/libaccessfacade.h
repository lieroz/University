#pragma once

#include <QObject>
#include <QScopedPointer>

#include <dataloaders/dataloaders.h>
#include <common/routestore.h>

class LibAccessFacade : public QObject
{
public:
    LibAccessFacade(QObject *parent = Q_NULLPTR);
    ~LibAccessFacade();

    void load(const QString &fileName);

private:
    QScopedPointer<AbstractDataLoader> m_loader;
    QScopedPointer<RouteStore> m_store;
};
