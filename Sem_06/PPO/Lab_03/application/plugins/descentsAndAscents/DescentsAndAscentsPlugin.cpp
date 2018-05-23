//
// Created by lieroz on 23.05.18.
//

#include <QtMath>
#include <QHBoxLayout>
#include <QDebug>

#include <DescentsAndAscentsPlugin.h>

DescentsAndAscentsPlugin::DescentsAndAscentsPlugin(QWidget *parent)
    : QWidget(parent)
{
    const qint32 length = LENGTH_CATHEGORIES_COUNT * STEEPNESS_CATHEGORIES_COUNT;
    m_cathegories = new qint32[length];

    m_lengthComboBox = new QComboBox(this);
    m_steepnessComboBox = new QComboBox(this);
    m_spinBox = new QSpinBox(this);
    m_spinBox->setReadOnly(true);
    m_spinBox->setMaximum(INT_MAX);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_lengthComboBox);
    layout->addWidget(m_steepnessComboBox);
    layout->addWidget(m_spinBox);

    for (auto i = 0; i < STEEPNESS_CATHEGORIES_COUNT; ++i) {
        m_steepnessComboBox->addItem(QString("Steepness cathegory: %1").arg(i + 1));

        if (i < LENGTH_CATHEGORIES_COUNT) {
            m_lengthComboBox->addItem(QString("Length cathegory: %1").arg(i + 1));
        }
    }

    for (auto i = 0; i < length; ++i) {
        m_cathegories[i] = 0;
    }

    setLayout(layout);
    setFixedSize({500, 100});
    setWindowTitle("Descents And Ascents Plugin");

    connect(m_lengthComboBox, SIGNAL(currentIndexChanged(qint32)), this, SLOT(setLengthCathegory(qint32)));
    connect(m_steepnessComboBox, SIGNAL(currentIndexChanged(qint32)), this, SLOT(setSteepnessCathegory(qint32)));
}

QString DescentsAndAscentsPlugin::name()
{
    return "DescentsAndAscentsPlugin";
}

void DescentsAndAscentsPlugin::exec(QSharedPointer<Route> route)
{
    for (auto i = 1; i < route->getPath().count(); ++i) {
        auto prev = route->getCoordinate(i - 1);
        auto curr = route->getCoordinate(i);
        const auto lengthCathegory = getLengthCathegory(prev, curr);
        const auto steepnessCathegory = getSteepnessCathegory(prev, curr);
        *((m_cathegories + lengthCathegory) + steepnessCathegory) += 1;
    }

    m_spinBox->setValue(*m_cathegories);
    show();
}

bool DescentsAndAscentsPlugin::isRunning()
{
    return isVisible();
}

void DescentsAndAscentsPlugin::setLengthCathegory(qint32 index)
{
    m_spinBox->setValue(*((m_cathegories + index) + m_steepnessComboBox->currentIndex()));
}

void DescentsAndAscentsPlugin::setSteepnessCathegory(qint32 index)
{
    m_spinBox->setValue(*((m_cathegories + index) + m_lengthComboBox->currentIndex()));
}

qint32 DescentsAndAscentsPlugin::getLengthCathegory(QSharedPointer<Coordinate> a, QSharedPointer<Coordinate> b)
{
    qreal distance = a->distanceTo(*b) * 1000;
    return distance > 500 ? 0 :
           distance >= 50 ? 1 : 2;
}

qint32 DescentsAndAscentsPlugin::getSteepnessCathegory(QSharedPointer<Coordinate> a, QSharedPointer<Coordinate> b)
{
    qreal height = qAbs(a->getAltitude() - b->getAltitude());
    qreal distance = a->distanceTo(*b) * 1000;
    qreal angle = qAtan(height / distance);
    return angle >= 35.0 ? 0 :
           angle >= 15.0 ? 1 :
           angle >= 8.0 ? 2 :
           angle >= 4.0 ? 3 : 4;
}
