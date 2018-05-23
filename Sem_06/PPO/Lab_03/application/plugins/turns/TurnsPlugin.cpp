//
// Created by lieroz on 22.05.18.
//

#include <QHBoxLayout>

#include <TurnsPlugin.h>

TurnsPlugin::TurnsPlugin(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    m_comboBox = new QComboBox(this);
    m_spinBox = new QSpinBox(this);
    m_spinBox->setMaximum(INT_MAX);

    layout->addWidget(m_comboBox);
    layout->addWidget(m_spinBox);

    setLayout(layout);
    setFixedSize({300, 100});
    setWindowTitle("Turns Plugin");

    for (auto i = 0; i < 8; ++i) {
        m_cathegories[i] = 0;
        m_comboBox->addItem(QString("Cathegory: %1").arg(i));
    }

    connect(m_comboBox, SIGNAL(currentIndexChanged(qint32)), this, SLOT(setSpinBoxData(qint32)));
}

QString TurnsPlugin::name()
{
    return "TurnsPlugin";
}

void TurnsPlugin::exec(QSharedPointer<Route> route)
{
    for (auto coordinate : route->getPath()) {
        m_cathegories[getCathegory(coordinate.getCourse())] += 1;
    }

    m_spinBox->setValue(m_cathegories[0]);
    show();
}

void TurnsPlugin::setSpinBoxData(qint32 index)
{
    m_spinBox->setValue(m_cathegories[index]);
}

qint32 TurnsPlugin::getCathegory(qreal angle)
{
    qreal value = angle / 0.9;
    return value <= 5.5 ? 0 :
           value <= 11.0 ? 1 :
           value <= 33.5 ? 2 :
           value <= 56.0 ? 3 :
           value <= 78.5 ? 4 :
           value <= 90.0 ? 5 :
           value <= 135 ? 6 : 7;
}
