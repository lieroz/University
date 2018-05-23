//
// Created by lieroz on 23.05.18.
//

#include <QtMath>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>

#include <SlopesPlugin.h>

SlopesPlugin::SlopesPlugin(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    m_spinBox = new QSpinBox(this);
    m_spinBox->setMaximum(INT_MAX);
    m_spinBox->setReadOnly(true);
    QLabel *label = new QLabel("Amount of steep slopes: ", this);

    layout->addWidget(label);
    layout->addWidget(m_spinBox);

    setLayout(layout);
    setFixedSize({350, 100});
    setWindowTitle("Slopes Plugin");
}

QString SlopesPlugin::name()
{
    return "SlopesPlugin";
}

void SlopesPlugin::exec(QSharedPointer<Route> route)
{
    qint32 count = 0;

    for (auto i = 1; i < route->getPath().count(); ++i) {
        auto prev = route->getCoordinate(i - 1);
        auto curr = route->getCoordinate(i);
        qreal distance = prev->distanceTo(*curr) * 1000;
        qreal height = qAbs(curr->getAltitude() - prev->getAltitude());

        // Or maybe Asin, but still 0...
        if (qAtan(height / distance) > STEEP_SLOPE_BOARDER) {
            ++count;
        }
    }

    m_spinBox->setValue(count);
    show();
}

bool SlopesPlugin::isRunning()
{
    return isVisible();
}
