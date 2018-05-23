//
// Created by lieroz on 23.05.18.
//

#ifndef SLOPESPLUGIN_H
#define SLOPESPLUGIN_H

#include <QWidget>
#include <QSpinBox>

#include <data/models/Route.h>

#include <../PluginInterface.h>

class SlopesPlugin : public QWidget, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.bmstu.SoftwareDesign.PluginInterface" FILE "slopesplugin.json")
    Q_INTERFACES(PluginInterface)

public:
    SlopesPlugin(QWidget *parent = nullptr);

    QString name() override;
    void exec(QSharedPointer<Route> route) override;
    bool isRunning() override;

private:
    QSpinBox *m_spinBox;
};

#endif // SLOPESPLUGIN_H
