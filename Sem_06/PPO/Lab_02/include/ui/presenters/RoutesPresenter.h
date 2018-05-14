//
// Created by lieroz on 10.05.18.
//

#ifndef LAB_02_ROUTESPRESENTER_H
#define LAB_02_ROUTESPRESENTER_H

#include <ui/presenters/IPresenter.h>

class RoutesPresenter : public IPresenter
{
    Q_OBJECT

public:
    RoutesPresenter(const QStringList &headers, QObject *parent = nullptr);

    qint32 rowCount(const QModelIndex &parent) const override;
    QVariant headerData(qint32 section, Qt::Orientation orientation, qint32 role) const override;
    QVariant data(const QModelIndex &index, qint32 role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, qint32 role = Qt::EditRole) override;

Q_SIGNALS:
    void routeNameChanged(qint32, const QString &);
};

#endif //LAB_02_ROUTESPRESENTER_H
