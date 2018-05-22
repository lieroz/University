//
// Created by lieroz on 10.05.18.
//

#ifndef LAB_02_COORDINATESPRESENTER_H
#define LAB_02_COORDINATESPRESENTER_H

#include <ui/presenters/IPresenter.h>
#include <data/models/Coordinate.h>

class CoordinatesPresenter : public IPresenter
{
    Q_OBJECT

public:
    CoordinatesPresenter(const QStringList &headers, QObject *parent = nullptr);

    qint32 rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, qint32 role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, qint32 role = Qt::EditRole) override;

    void setCurrentRouteIndex(qint32 index);

Q_SIGNALS:
    void updateCoordinate(qint32 index, const Coordinate &oldCoordinate, const Coordinate &newCoordinate);

private:
    qint32 m_currentRoute;
};

#endif //LAB_02_COORDINATESPRESENTER_H
