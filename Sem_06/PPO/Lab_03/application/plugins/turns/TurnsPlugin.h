//
// Created by lieroz on 22.05.18.
//

#ifndef TURNSPLUGIN_H
#define TURNSPLUGIN_H

#include <QString>

#include <../PluginInterface.h>

class TurnsPlugin : public QObject, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.bmstu.SoftwareDesign.PluginInterface" FILE "turnsplugin.json")
    Q_INTERFACES(PluginInterface)

public:
    QString echo(const QString &message) override;
};

#endif // TURNSPLUGIN_H
