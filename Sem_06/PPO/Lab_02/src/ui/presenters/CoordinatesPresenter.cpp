//
// Created by lieroz on 10.05.18.
//

#include <data/RuntimeStorage.h>
#include <QDebug>

#include <ui/presenters/CoordinatesPresenter.h>

CoordinatesPresenter::CoordinatesPresenter(const QStringList &headers, QObject *parent)
    : IPresenter(headers, parent)
{
    m_currentRoute = -1;
}

qint32 CoordinatesPresenter::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (m_currentRoute == -1) {
        return 0;
    }
    return RuntimeStorage::instance().getRoute(m_currentRoute)->getPath().count();
}

QVariant CoordinatesPresenter::data(const QModelIndex &index, qint32 role) const
{
    if (role == Qt::DisplayRole) {
        auto coordinate =
            RuntimeStorage::instance().getRoute(m_currentRoute)->getCoordinate(index.row());
        switch (index.column()) {
        case 0:
            return coordinate->getLatitude();
        case 1:
            return coordinate->getLongitude();
        case 2:
            return coordinate->getAltitude();
        default:
            return QVariant();
        }
    }
    return QVariant();
}

Qt::ItemFlags CoordinatesPresenter::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool CoordinatesPresenter::setData(const QModelIndex &index, const QVariant &value, qint32 role)
{
    if (index.isValid() && role == Qt::EditRole) {
        auto route = RuntimeStorage::instance().getRoute(m_currentRoute);
        auto result = route->getCoordinate(index.row());
        if (result == nullptr) {
            return false;
        }

        Coordinate oldCoordinate = *result;
        Coordinate newCoordinate = *result;
        bool ok = false;
        qreal cellValue = value.toDouble(&ok);

        if (ok) {
            switch (index.column()) {
            case 0:
                newCoordinate.setLatitude(cellValue);
                break;
            case 1:
                newCoordinate.setLongitude(cellValue);
                break;
            case 2:
                newCoordinate.setAltitude(cellValue);
                break;
            default:
                break;
            }

            if (oldCoordinate != newCoordinate) {
                route->updateCoordinate(index.row(), newCoordinate);
                emit dataChanged(index, index);
                emit updateCoordinate(index.row(), oldCoordinate, newCoordinate);
                return true;
            }
        }
    }

    return false;
}

void CoordinatesPresenter::setCurrentRouteIndex(qint32 index)
{
    m_currentRoute = index;
}
