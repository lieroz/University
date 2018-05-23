//
// Created by lieroz on 23.05.18.
//

#ifndef DESCENTSANDASCENTSPLUGIN_H
#define DESCENTSANDASCENTSPLUGIN_H

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QMap>

#include <data/models/Route.h>

#include <../PluginInterface.h>

class DescentsAndAscentsPlugin : public QWidget, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ru.bmstu.SoftwareDesign.PluginInterface" FILE "descents_and_ascentsplugin.json")
    Q_INTERFACES(PluginInterface)

    const qint32 LENGTH_CATHEGORIES_COUNT = 3;
    const qint32 STEEPNESS_CATHEGORIES_COUNT = 5;

public:
    DescentsAndAscentsPlugin(QWidget *parent = nullptr);

    QString name() override;
    void exec(QSharedPointer<Route> route) override;
    bool isRunning() override;

private Q_SLOTS:
    void setLengthCathegory(qint32 index);
    void setSteepnessCathegory(qint32 index);

private:
    qint32 getLengthCathegory(QSharedPointer<Coordinate> a, QSharedPointer<Coordinate> b);
    qint32 getSteepnessCathegory(QSharedPointer<Coordinate> a, QSharedPointer<Coordinate> b);

private:
    QComboBox *m_lengthComboBox;
    QComboBox *m_steepnessComboBox;
    QSpinBox *m_spinBox;
    qint32 *m_cathegories;
};

#endif // DESCENTSANDASCENTSPLUGIN_H
