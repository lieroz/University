#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickView>
#include <QFileDialog>
#include <QDir>
#include <QQmlContext>

QVector<QString> routeInfoTableViewColumnNames = {"Name", "Length (km)", "Date"};
QVector<QString> routeTableViewColumnNames = {"Longitude", "Latitude"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_accessor.reset(new LibAccessFacade(this));

    m_mapViewProxy.reset(new MapViewProxy);
    QQuickView *view = new QQuickView;
    view->rootContext()->setContextProperty("mapViewProxy", m_mapViewProxy.data());
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl(QStringLiteral("qrc:/gui/resources/qml/MapView.qml")));
    ui->tabWidget->addTab(container, "MapView");

    setUpActions();
    setUpRouteDataView();
    setUpRouteCoordinatesView();
}

MainWindow::~MainWindow()
{

}

void MainWindow::routeInfoTableItemChanged(QTableWidgetItem *item)
{

}

void MainWindow::routeInfoTableRowSelected(QModelIndex index)
{
    Route route = m_accessor->getRoute(index.row());
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

    emit m_mapViewProxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
}

void MainWindow::routeTableItemChanged(QTableWidgetItem *item)
{

}

void MainWindow::routeTableRowSelected(QModelIndex index)
{

}

void MainWindow::openFile()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                            tr("FileDialog"), QDir::homePath(), tr("Gpx Files (*.gpx)"));

    Q_FOREACH (QString fileName, fileNames) {
        Route route = m_accessor->load(fileName);
        const auto rowCount = ui->routeInfoTableView->rowCount();
        ui->routeInfoTableView->insertRow(rowCount);

        ui->routeInfoTableView->setItem(rowCount, 0, new QTableWidgetItem(route.getName()));
        ui->routeInfoTableView->setItem(rowCount, 1, new QTableWidgetItem(QString::number(route.getLength() / 1000)));
        ui->routeInfoTableView->setItem(rowCount, 2, new QTableWidgetItem(route.getDate().toString()));
    }
}

void MainWindow::setUpActions()
{
    connect(ui->openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
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

    connect(ui->routeTableView, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(routeTableItemChanged(QTableWidgetItem *)));
    connect(ui->routeTableView, SIGNAL(pressed(QModelIndex)),
            this, SLOT(routeTableRowSelected(QModelIndex)));
}
