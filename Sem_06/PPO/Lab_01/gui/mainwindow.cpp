#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickView>
#include <QFileDialog>
#include <QDir>
#include <QQmlContext>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>

#include <commands/commands.h>

QVector<QString> routeInfoTableViewColumnNames = {"Name", "Length (km)", "Date"};
QVector<QString> routeTableViewColumnNames = {"Latitude", "Longitude"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    m_accessor(new LibAccessFacade), m_mapViewProxy(new MapViewProxy)
{
    m_undoStack = new QUndoStack(this);
    m_selectedRow = 0;
    m_routeInfoTableCellModified = false;
    m_routeTableCellModified = false;

    ui->setupUi(this);
    ui->label->setTextInteractionFlags(Qt::TextSelectableByMouse);

    QQuickView *view = new QQuickView;
    view->rootContext()->setContextProperty("mapViewProxy", m_mapViewProxy.data());
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl(QStringLiteral("qrc:/gui/resources/qml/MapView.qml")));
    ui->tabWidget->addTab(container, "MapView");

    setUpActions();
    setUpRouteDataView();
    setUpRouteCoordinatesView();

    ui->mainToolBar->addAction(m_undoAction);
    ui->mainToolBar->addAction(m_redoAction);
}

MainWindow::~MainWindow()
{

}

void MainWindow::routeInfoTableItemDoubleClicked(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);

    m_routeInfoTableCellModified = true;
}

void MainWindow::routeInfoTableItemChanged(QTableWidgetItem *item)
{
    if (m_routeInfoTableCellModified) {
        Route &route = m_accessor->getRoute(item->row());
        route.setName(item->text());
    }
}

void MainWindow::routeInfoTableRowSelected(QModelIndex index)
{
    Route &route = m_accessor->getRoute(index.row());
    if (ui->routeTableView->rowCount() != 0) {
        ui->routeTableView->clearContents();
    }
    ui->routeTableView->setRowCount(0);

    for (auto i = 0; i < route.getCoordinates().size(); ++i) {
        const auto coord = route.getCoordinates().coordinateAt(i);
        const auto rowCount = ui->routeTableView->rowCount();
        ui->routeTableView->insertRow(rowCount);
        ui->routeTableView->setItem(rowCount, 0, new QTableWidgetItem(QString::number(coord.latitude())));
        ui->routeTableView->setItem(rowCount, 1, new QTableWidgetItem(QString::number(coord.longitude())));
    }

    m_selectedRow = index.row();
    ui->label->setText(route.getPolyline());
    emit m_mapViewProxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
}

void MainWindow::routeTableItemDoubleClicked(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);

    m_routeTableCellModified = true;
}

void MainWindow::routeTableItemChanged(QTableWidgetItem *item)
{
    if (m_routeTableCellModified) {
        Route &route = m_accessor->getRoute(m_selectedRow);
        QGeoCoordinate coord = route.getCoordinates().coordinateAt(item->row());
        bool ok = false;
        qreal number = item->text().toDouble(&ok);

        if (!ok) {
            item->setText(item->column() == 0 ? QString::number(coord.latitude()) : QString::number(coord.longitude()));
            QMessageBox::warning(nullptr, "Warning", "This field accepts only double type", QMessageBox::Ok);
            return;
        }

        if (item->column() == 0) {
            if (number < -90.0 || number > 90.0) {
                item->setText(QString::number(coord.latitude()));
                QMessageBox::warning(nullptr, "Warning", "Latitude can't be more than 90 and less than -90", QMessageBox::Ok);
                return;
            }

            coord.setLatitude(number);
        } else {
            if (number < -180.0 || number > 180.0) {
                item->setText(QString::number(coord.longitude()));
                QMessageBox::warning(nullptr, "Warning", "Longitude can't be more than 180 and less than -180", QMessageBox::Ok);
                return;
            }

            coord.setLongitude(number);
        }

        route.replaceCoordinate(item->row(), coord);
        route.updateLength();
        ui->routeInfoTableView->item(m_selectedRow, 1)->setText(QString::number(route.getLength() / 1000));
        emit m_mapViewProxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
        m_routeTableCellModified = false;
    }
}

void MainWindow::receiveFromWidget(QString text)
{
    QGeoPath geoPath = PolylineEncoder::decode(text);
    Route route;
    route.appendCoordinates(geoPath);
    route.updateLength();

    const auto rowCount = ui->routeInfoTableView->rowCount();
    m_undoStack->push(new AddRouteCommand(rowCount, route, ui->routeInfoTableView));
}

void MainWindow::importRoutes()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                            tr("FileDialog"), QDir::homePath(), tr("Gpx Files (*.gpx)"));

    Q_FOREACH (QString fileName, fileNames) {
        Route route;
        m_accessor->load(fileName, route);
        const auto rowCount = ui->routeInfoTableView->rowCount();
        m_undoStack->push(new AddRouteCommand(rowCount, route, ui->routeInfoTableView));
    }
}

void MainWindow::importRoute()
{
    Widget *widget = new Widget;
    connect(widget, SIGNAL(sendToMainWindow(QString)), this, SLOT(receiveFromWidget(QString)));
    widget->show();
}

void MainWindow::createRoute()
{
    Route route;
    const auto rowCount = ui->routeInfoTableView->rowCount();
    m_undoStack->push(new AddRouteCommand(rowCount, route, ui->routeInfoTableView));
}

void MainWindow::deleteRoutes()
{
    const auto size = ui->routeInfoTableView->selectionModel()->selectedRows().size();

    for (auto i = 0; i < size; ++i) {
        const auto index = ui->routeInfoTableView->selectionModel()->selectedRows().first().row();
        m_undoStack->push(new DeleteRouteCommand(index, ui->routeInfoTableView));
    }

    if (ui->routeTableView->rowCount() != 0) {
        ui->routeTableView->clearContents();
    }

    ui->routeTableView->setRowCount(0);
}

void MainWindow::addPoint()
{
    if (ui->routeInfoTableView->selectionModel()->selectedRows().size() != 0) {
        Route &route = m_accessor->getRoute(m_selectedRow);
        QGeoCoordinate coord(0, 0);
        route.appendCoordinate(coord);
        const auto rowCount = ui->routeTableView->rowCount();

        ui->routeTableView->insertRow(rowCount);
        ui->routeTableView->setItem(rowCount, 0, new QTableWidgetItem(QString::number(0)));
        ui->routeTableView->setItem(rowCount, 1, new QTableWidgetItem(QString::number(0)));
    }
}

void MainWindow::removePoints()
{
    const auto size = ui->routeTableView->selectionModel()->selectedRows().size();
    Route &route = m_accessor->getRoute(m_selectedRow);

    for (auto i = 0; i < size; ++i) {
        const auto index = ui->routeTableView->selectionModel()->selectedRows().first().row();
        ui->routeTableView->removeRow(index);
        route.removeCoordinate(index);
    }

    route.updateLength();
    ui->routeInfoTableView->item(m_selectedRow, 1)->setText(QString::number(route.getLength() / 1000));
    emit m_mapViewProxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
}

void MainWindow::setUpActions()
{
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(importRoutes()));
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(importRoute()));
    connect(ui->actionCreate, SIGNAL(triggered()), this, SLOT(createRoute()));
    connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(deleteRoutes()));
    connect(ui->actionAdd, SIGNAL(triggered()), this, SLOT(addPoint()));
    connect(ui->actionRemove, SIGNAL(triggered()), this, SLOT(removePoints()));

    m_undoAction = m_undoStack->createUndoAction(this, tr("&Undo"));
    m_undoAction->setShortcuts(QKeySequence::Undo);
    m_redoAction = m_undoStack->createRedoAction(this, tr("&Redo"));
    m_redoAction->setShortcuts(QKeySequence::Redo);
}

void MainWindow::setUpRouteDataView()
{
    ui->routeInfoTableView->setColumnCount(routeInfoTableViewColumnNames.size());
    ui->routeInfoTableView->setFocusPolicy(Qt::NoFocus);
    ui->routeInfoTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (auto i = 0; i < routeInfoTableViewColumnNames.size(); ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(routeInfoTableViewColumnNames.at(i));
        ui->routeInfoTableView->setHorizontalHeaderItem(i, item);
    }

    connect(ui->routeInfoTableView, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(routeInfoTableItemChanged(QTableWidgetItem *)));
    connect(ui->routeInfoTableView, SIGNAL(pressed(QModelIndex)),
            this, SLOT(routeInfoTableRowSelected(QModelIndex)));
}

void MainWindow::setUpRouteCoordinatesView()
{
    ui->routeTableView->setColumnCount(routeTableViewColumnNames.size());
    ui->routeTableView->setFocusPolicy(Qt::NoFocus);
    ui->routeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (auto i = 0; i < routeTableViewColumnNames.size(); ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(routeTableViewColumnNames.at(i));
        ui->routeTableView->setHorizontalHeaderItem(i, item);
    }

    connect(ui->routeTableView, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(routeTableItemDoubleClicked(int, int)));
    connect(ui->routeTableView, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(routeTableItemChanged(QTableWidgetItem *)));
}
