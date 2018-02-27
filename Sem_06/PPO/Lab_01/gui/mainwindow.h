#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QTableWidgetItem>

#include <libaccessfacade.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void routeInfoTableItemChanged(QTableWidgetItem *item);
    void routeInfoTableColumnSelected(QModelIndex index);

    void routeTableItemChanged(QTableWidgetItem *item);
    void routeTableColumnSelected(QModelIndex index);

    void openFile();

private:
    void setUpActions();
    void setUpRouteDataView();
    void setUpRouteCoordinatesView();

private:
    QScopedPointer<Ui::MainWindow> ui;
    QScopedPointer<LibAccessFacade> m_accessor;
};

#endif // MAINWINDOW_H
