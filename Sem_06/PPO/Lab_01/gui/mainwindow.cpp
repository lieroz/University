#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickView>
#include <QFileDialog>
#include <QDir>

QVector<QString> routeInfoTableViewColumnNames = {"Name", "Length", "Date"};
QVector<QString> routeTableViewColumnNames = {"Longitude", "Latitude"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_accessor.reset(new LibAccessFacade(this));

    QQuickView *view = new QQuickView();
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
    qDebug() << item->column() << " " << item->row();
}

void MainWindow::routeInfoTableColumnSelected(QModelIndex index)
{
    qDebug() << index.row();
}

void MainWindow::routeTableItemChanged(QTableWidgetItem *item)
{
    qDebug() << item->column() << " " << item->row();
}

void MainWindow::routeTableColumnSelected(QModelIndex index)
{
    qDebug() << index.row();
}

void MainWindow::openFile()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                            tr("FileDialog"), QDir::homePath(), tr("Gpx Files (*.gpx)"));

    Q_FOREACH (QString fileName, fileNames) {
        m_accessor->load(fileName);
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
            this, SLOT(routeInfoTableColumnSelected(QModelIndex)));

    ui->routeInfoTableView->insertRow(ui->routeInfoTableView->rowCount());
    ui->routeInfoTableView->insertRow(ui->routeInfoTableView->rowCount());
    ui->routeInfoTableView->insertRow(ui->routeInfoTableView->rowCount());
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
            this, SLOT(routeTableColumnSelected(QModelIndex)));

    ui->routeTableView->insertRow(ui->routeTableView->rowCount());
    ui->routeTableView->insertRow(ui->routeTableView->rowCount());
    ui->routeTableView->insertRow(ui->routeTableView->rowCount());
}
