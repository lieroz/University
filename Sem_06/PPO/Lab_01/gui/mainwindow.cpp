#include <mainwindow.h>
#include <ui_mainwindow.h>

#include <QQuickView>
#include <QFileDialog>
#include <QDir>
#include <QQmlContext>
#include <QMessageBox>
#include <QTableWidget>

#include <commands.h>

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
    delete ui;
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
        QSharedPointer<Route> route = m_accessor->getRoute(item->row());
        route->setName(item->text());
        m_routeInfoTableCellModified = false;
    }
}

void MainWindow::routeInfoTableRowSelected(QModelIndex index)
{
    QSharedPointer<Route> route = m_accessor->getRoute(index.row());
    clearRouteTableView();
    populateRouteTableView(route);
    m_selectedRow = index.row();
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
        QSharedPointer<Route> route = m_accessor->getRoute(m_selectedRow);
        QGeoCoordinate coord = route->getCoordinates().coordinateAt(item->row());
        QGeoCoordinate oldCoord = coord;
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

        auto undoRedoFunc = std::bind(&MainWindow::modifyPointCommand, this, std::placeholders::_1, m_selectedRow, item->row());
        m_undoStack->push(new ModifyPointCommand(coord, oldCoord, undoRedoFunc));
        m_routeTableCellModified = false;
    }
}

void MainWindow::receiveFromWidget(QString text)
{
    QGeoPath geoPath = PolylineEncoder::decode(text);
    QSharedPointer<Route> route(new Route);
    route->appendCoordinates(geoPath);
    route->updateLength();

    const auto rowCount = ui->routeInfoTableView->rowCount();
    auto redoFunc = std::bind(&MainWindow::addRouteCommand, this, std::placeholders::_1, rowCount);
    auto undoFunc = std::bind(&MainWindow::removeRouteCommand, this, rowCount);
    m_undoStack->push(new AddRouteCommand(route, redoFunc, undoFunc));
}

void MainWindow::importRoutes()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                            tr("FileDialog"), QDir::homePath(), tr("Gpx Files (*.gpx)"));

    Q_FOREACH (QString fileName, fileNames) {
        QSharedPointer<Route> route(new Route);
        m_accessor->load(fileName, route);
        const auto rowCount = ui->routeInfoTableView->rowCount();
        auto redoFunc = std::bind(&MainWindow::addRouteCommand, this, std::placeholders::_1, rowCount);
        auto undoFunc = std::bind(&MainWindow::removeRouteCommand, this, rowCount);
        m_undoStack->push(new AddRouteCommand(route, redoFunc, undoFunc));
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
    QSharedPointer<Route> route(new Route);
    const auto rowCount = ui->routeInfoTableView->rowCount();
    auto redoFunc = std::bind(&MainWindow::addRouteCommand, this, std::placeholders::_1, rowCount);
    auto undoFunc = std::bind(&MainWindow::removeRouteCommand, this, rowCount);
    m_undoStack->push(new AddRouteCommand(route, redoFunc, undoFunc));
}

void MainWindow::deleteRoutes()
{
    const auto size = ui->routeInfoTableView->selectionModel()->selectedRows().size();

    for (auto i = 0; i < size; ++i) {
        const auto index = ui->routeInfoTableView->selectionModel()->selectedRows().first().row();
        QSharedPointer<Route> route = m_accessor->getRoute(index);
        auto redoFunc = std::bind(&MainWindow::removeRouteCommand, this, index);
        auto undoFunc = std::bind(&MainWindow::addRouteCommand, this, std::placeholders::_1, index);
        m_undoStack->push(new DeleteRouteCommand(route, redoFunc, undoFunc));
    }
}

void MainWindow::addPoint()
{
    if (ui->routeInfoTableView->selectionModel()->selectedRows().size() != 0) {
        const auto rowCount = ui->routeTableView->rowCount();
        auto redoFunc = std::bind(&MainWindow::addPointCommand, this, std::placeholders::_1, m_selectedRow, rowCount);
        auto undoFunc = std::bind(&MainWindow::removePointCommand, this, m_selectedRow, rowCount);
        m_undoStack->push(new AddPointCommand(QGeoCoordinate(0, 0), redoFunc, undoFunc));
    }
}

void MainWindow::removePoints()
{
    const auto size = ui->routeTableView->selectionModel()->selectedRows().size();

    for (auto i = 0; i < size; ++i) {
        const auto index = ui->routeTableView->selectionModel()->selectedRows().first().row();
        auto redoFunc = std::bind(&MainWindow::removePointCommand, this, m_selectedRow, index);
        auto undoFunc = std::bind(&MainWindow::addPointCommand, this, std::placeholders::_1, m_selectedRow, index);
        QGeoCoordinate point = m_accessor->getRoute(m_selectedRow)->getCoordinates().coordinateAt(index);
        m_undoStack->push(new DeletePointCommand(point, redoFunc, undoFunc));
    }
}

void MainWindow::populateRouteTableView(QSharedPointer<Route> route)
{
    for (auto i = 0; i < route->getCoordinates().size(); ++i) {
        const auto coord = route->getCoordinates().coordinateAt(i);
        const auto rowCount = ui->routeTableView->rowCount();
        ui->routeTableView->insertRow(rowCount);
        ui->routeTableView->setItem(rowCount, 0, new QTableWidgetItem(QString::number(coord.latitude())));
        ui->routeTableView->setItem(rowCount, 1, new QTableWidgetItem(QString::number(coord.longitude())));
    }

    ui->label->setText(route->getPolyline());
    emit m_mapViewProxy->setPolyline(QVariant::fromValue(route->getCoordinates()));
}

void MainWindow::clearRouteTableView()
{
    if (ui->routeTableView->rowCount() != 0) {
        ui->routeTableView->clearContents();
    }

    ui->routeTableView->setRowCount(0);
    QGeoPath path;
    path.addCoordinate(QGeoCoordinate(0, 0));
    emit m_mapViewProxy->setPolyline(QVariant::fromValue(path));
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

    connect(ui->routeInfoTableView, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(routeInfoTableItemDoubleClicked(int, int)));
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

void MainWindow::addRouteCommand(QSharedPointer<Route> route, qint32 index)
{
    ui->routeInfoTableView->insertRow(index);
    ui->routeInfoTableView->setItem(index, 0, new QTableWidgetItem(route->getName()));

    QTableWidgetItem *item;
    item = new QTableWidgetItem(QString::number(route->getLength() / 1000));
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->routeInfoTableView->setItem(index, 1, item);

    item = new QTableWidgetItem(route->getDate().toString());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->routeInfoTableView->setItem(index, 2, item);
    m_accessor->addRoute(route);

    if (m_selectedRow == index) {
        populateRouteTableView(route);
    }
}

void MainWindow::removeRouteCommand(qint32 index)
{
    ui->routeInfoTableView->removeRow(index);
    m_accessor->deleteRoute(index);

    if (m_selectedRow == index) {
        clearRouteTableView();
    }
}

void MainWindow::addPointCommand(QGeoCoordinate &point, qint32 routeIndex, qint32 pointIndex)
{
    ui->routeTableView->insertRow(pointIndex);
    ui->routeTableView->setItem(pointIndex, 0, new QTableWidgetItem(QString::number(point.latitude())));
    ui->routeTableView->setItem(pointIndex, 1, new QTableWidgetItem(QString::number(point.longitude())));
    QSharedPointer<Route> route = m_accessor->getRoute(routeIndex);
    route->insertCoordinate(pointIndex, point);
    route->updateLength();
    ui->routeInfoTableView->item(routeIndex, 1)->setText(QString::number(route->getLength() / 1000));
    emit m_mapViewProxy->setPolyline(QVariant::fromValue(route->getCoordinates()));
}

void MainWindow::modifyPointCommand(QGeoCoordinate &point, qint32 routeIndex, qint32 pointIndex)
{
    QSharedPointer<Route> route = m_accessor->getRoute(routeIndex);
    route->replaceCoordinate(pointIndex, point);
    route->updateLength();
    ui->routeInfoTableView->item(routeIndex, 1)->setText(QString::number(route->getLength() / 1000));

    if (m_selectedRow == routeIndex) {
        ui->routeTableView->item(pointIndex, 0)->setText(QString::number(point.latitude()));
        ui->routeTableView->item(pointIndex, 1)->setText(QString::number(point.longitude()));
        emit m_mapViewProxy->setPolyline(QVariant::fromValue(route->getCoordinates()));
    }
}

void MainWindow::removePointCommand(qint32 routeIndex, qint32 pointIndex)
{
    ui->routeTableView->removeRow(pointIndex);
    QSharedPointer<Route> route = m_accessor->getRoute(routeIndex);
    route->removeCoordinate(pointIndex);
    route->updateLength();
    ui->routeInfoTableView->item(routeIndex, 1)->setText(QString::number(route->getLength() / 1000));
    emit m_mapViewProxy->setPolyline(QVariant::fromValue(route->getCoordinates()));
}
