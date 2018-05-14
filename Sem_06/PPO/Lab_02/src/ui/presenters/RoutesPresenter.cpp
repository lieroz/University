//
// Created by lieroz on 10.05.18.
//

#include <data/RuntimeStorage.h>

#include <ui/presenters/RoutesPresenter.h>

RoutesPresenter::RoutesPresenter(const QStringList &headers, QObject *parent)
    : IPresenter(headers, parent)
{
}

qint32 RoutesPresenter::rowCount(const QModelIndex &parent) const
{
    return RuntimeStorage::instance().count();
}

QVariant RoutesPresenter::headerData(qint32 section, Qt::Orientation orientation, qint32 role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        return m_headers[section];
    }
    if (orientation == Qt::Vertical) {
        return QString::number(section + 1);
    }
    return QVariant();
}

QVariant RoutesPresenter::data(const QModelIndex &index, qint32 role) const
{
    if (role == Qt::DisplayRole) {
        auto route = RuntimeStorage::instance().getRoute(index.row());
        switch (index.column()) {
        case 0:
            return route->getName();
        case 1:
            return route->getLength();
        case 2:
            return route->getCreated();
        default:
            return QVariant();
        }
    }
    return QVariant();
}

Qt::ItemFlags RoutesPresenter::flags(const QModelIndex &index) const
{
    if (index.column() == 0) {
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    }
    return QAbstractTableModel::flags(index) & ~Qt::ItemIsSelectable;
}

bool RoutesPresenter::setData(const QModelIndex &index, const QVariant &value, qint32 role)
{
    if (index.isValid() && role == Qt::EditRole) {
        auto route = RuntimeStorage::instance().getRoute(index.row());
        if (index.column() == 0 && !value.toString().isEmpty()) {
            route->setName(value.toString());

            emit routeNameChanged(index.row(), route->getName());
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}
