//
// Created by lieroz on 13.05.18.
//

#include <ui/presenters/IPresenter.h>


IPresenter::IPresenter(const QStringList &headers, QObject *parent)
    : m_headers(headers), QAbstractTableModel(parent)
{
}

qint32 IPresenter::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_headers.count();
}

QVariant IPresenter::headerData(qint32 section, Qt::Orientation orientation, qint32 role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        return m_headers[section];
    }
    return QVariant();
}

void IPresenter::clear()
{
    beginResetModel();
    endResetModel();
}
