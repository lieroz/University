//
// Created by lieroz on 22.05.18.
//

#ifndef TURNSPLUGIN_H
#define TURNSPLUGIN_H

#include <QString>
#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QMap>

#include <../PluginInterface.h>

class TurnsPlugin : public QWidget, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.bmstu.SoftwareDesign.PluginInterface" FILE "turnsplugin.json")
    Q_INTERFACES(PluginInterface)

public:
    TurnsPlugin(QWidget *parent = nullptr);

    QString name() override;
    void exec(QSharedPointer<Route> route) override;
    bool isRunning() override;

private Q_SLOTS:
    void setSpinBoxData(qint32 index);

private:
    qint32 getCathegory(qreal angle);

private:
    QComboBox *m_comboBox;
    QSpinBox *m_spinBox;
    QMap<qint32, qint32> m_cathegories;
};

#endif // TURNSPLUGIN_H
