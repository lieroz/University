//
// Created by lieroz on 23.05.18.
//

#ifndef DESCENTSANDASCENTSPLUGIN_H
#define DESCENTSANDASCENTSPLUGIN_H

#include <QWidget>

#include <../PluginInterface.h>

class DescentsAndAscentsPlugin : public QWidget, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.bmstu.SoftwareDesign.PluginInterface" FILE "descents_and_ascentsplugin.json")
    Q_INTERFACES(PluginInterface)

public:
    DescentsAndAscentsPlugin(QWidget *parent = nullptr);

    QString name() override;
    void exec(QSharedPointer<Route> route) override;
    bool isRunning() override;

private Q_SLOTS:

private:

};

#endif // DESCENTSANDASCENTSPLUGIN_H
