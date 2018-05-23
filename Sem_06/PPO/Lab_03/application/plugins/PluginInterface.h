//
// Created by lieroz on 22.05.18.
//

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QString>

#include <data/models/Route.h>

class PluginInterface
{
public:
    virtual ~PluginInterface() = default;

    virtual QString name() = 0;
    virtual void exec(QSharedPointer<Route> route) = 0;
};

#define PluginInterface_iid "ru.bmstu.SoftwareDesign.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif // PLUGININTERFACE_H
