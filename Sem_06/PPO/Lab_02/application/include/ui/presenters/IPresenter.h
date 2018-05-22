//
// Created by lieroz on 12.05.18.
//

#ifndef LAB_02_IPRESENTER_H
#define LAB_02_IPRESENTER_H

#include <QAbstractTableModel>
#include <QStringList>

class IPresenter : public QAbstractTableModel
{
    Q_OBJECT

public:
    IPresenter(const QStringList &headers, QObject *parent = nullptr);

    qint32 columnCount(const QModelIndex &parent) const override;
    QVariant headerData(qint32 section, Qt::Orientation orientation, qint32 role) const override;

    virtual void clear();

protected:
    QStringList m_headers;
};

#endif //LAB_02_IPRESENTER_H
