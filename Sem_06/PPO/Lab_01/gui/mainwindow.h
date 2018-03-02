#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QTableWidgetItem>
#include <QQuickItem>
#include <QUndoStack>

#include <libaccessfacade.h>
#include "widget.h"

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
    ~MainWindow() = default;

private Q_SLOTS:
    void routeInfoTableItemDoubleClicked(int row, int column);
    void routeInfoTableItemChanged(QTableWidgetItem *item);
    void routeInfoTableRowSelected(QModelIndex index);

    void routeTableItemDoubleClicked(int row, int column);
    void routeTableItemChanged(QTableWidgetItem *item);

    void receiveFromWidget(QString text);

    void importRoutes();
    void importRoute();
    void createRoute();
    void deleteRoutes();

    void addPoint();
    void removePoints();

private:
    void setUpActions();
    void setUpRouteDataView();
    void setUpRouteCoordinatesView();

private:
    Ui::MainWindow *ui;
    MapViewProxy *m_mapViewProxy;

    QScopedPointer<LibAccessFacade> m_accessor;

    QUndoStack *m_undoStack;
    QAction *m_undoAction;
    QAction *m_redoAction;

    qint32 m_selectedRow;
    bool m_routeInfoTableCellModified;
    bool m_routeTableCellModified;
};

#endif // MAINWINDOW_H
