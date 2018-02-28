#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QTableWidgetItem>
#include <QQuickItem>

#include <libaccessfacade.h>

namespace Ui
{
class MainWindow;
}

class MapViewProxy : public QQuickItem
{
    Q_OBJECT

public:
    MapViewProxy(QQuickItem *parent = Q_NULLPTR) : QQuickItem(parent) {}
    virtual ~MapViewProxy() = default;

Q_SIGNALS:
    void setPolyline(const QVariant& geopath);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void routeInfoTableItemChanged(QTableWidgetItem *item);
    void routeInfoTableRowSelected(QModelIndex index);

    void routeTableItemChanged(QTableWidgetItem *item);
    void routeTableRowSelected(QModelIndex index);

    void importRoutes();
    void createRoute();
    void deleteRoutes();

    void addPoint();
    void modifyPoint();
    void removePoint();

    void undo();
    void redo();

private:
    void setUpActions();
    void setUpRouteDataView();
    void setUpRouteCoordinatesView();

private:
    QScopedPointer<Ui::MainWindow> ui;
    QScopedPointer<LibAccessFacade> m_accessor;
    QScopedPointer<MapViewProxy> m_mapViewProxy;
};

#endif // MAINWINDOW_H
