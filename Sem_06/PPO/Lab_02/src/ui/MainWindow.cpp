//
// Created by lieroz on 13.05.18.
//

#include <QFileDialog>
#include <QMessageBox>

#include <data/DataRW.h>
#include <data/RuntimeStorage.h>

#include <ui/commands/AddRouteCommand.h>
#include <ui/commands/RemoveRouteCommand.h>
#include <ui/commands/AddCoordinateCommand.h>
#include <ui/commands/UpdateCoordinateCommand.h>
#include <ui/commands/RemoveCoordinateCommand.h>
#include <ui/AddCoordinateDialog.h>

#include <ui/MainWindow.h>
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList routesViewHeaders = {"Name", "Length", "Created"};
    m_routesPresenter = new RoutesPresenter(routesViewHeaders, this);
    ui->routesView->setModel(m_routesPresenter);
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList coordinatesViewHeaders = {"Latitude", "Longitude", "Altitude"};
    m_coordinatesPresenter = new CoordinatesPresenter(coordinatesViewHeaders, this);
    ui->coordinatesView->setModel(m_coordinatesPresenter);
    m_delegate = new SpinBoxDelegate(this);
    ui->coordinatesView->setItemDelegate(m_delegate);
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(m_coordinatesPresenter, SIGNAL(updateCoordinate(qint32, Coordinate, Coordinate)),
            this, SLOT(coordinateChanged(qint32, Coordinate, Coordinate)));

    m_undoStack = new QUndoStack(this);

    QAction *undoAction = m_undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);
    QAction *redoAction = m_undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);

    ui->menuFile->addSeparator();
    ui->menuFile->addAction(undoAction);
    ui->menuFile->addAction(redoAction);

    ui->comboBox->addItem(tr("nothing"));
    connect(m_routesPresenter, SIGNAL(routeNameChanged(qint32, QString)),
            this, SLOT(updateComboBox(qint32, QString)));

    m_addCoordinateDialog = new AddCoordinateDialog(this);
    connect(m_addCoordinateDialog, SIGNAL(sendCoordinate(qint32, Coordinate)),
            this, SLOT(recieveCoordinate(qint32, Coordinate)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList fileNames =
        QFileDialog::getOpenFileNames(this, tr("FileDialog"), QDir::homePath(), tr("Gpx Files (*.gpx)"));

    for (const auto &fileName : fileNames) {
        QFileInfo fileInfo(fileName);
        auto rwFuncs = getRWFunctions(fileInfo.completeSuffix());
        QSharedPointer<Route> route = rwFuncs.first(fileName);
        qint32 index = RuntimeStorage::instance().count();

        auto redoFunc = std::bind(&MainWindow::addRoute, this, std::placeholders::_1, index);
        auto undoFunc = std::bind(&MainWindow::removeRoute, this, index);
        m_undoStack->push(new AddRouteCommand(route, redoFunc, undoFunc));
    }
}

void MainWindow::on_actionImport_triggered()
{
}

void MainWindow::on_actionSave_triggered()
{
    qint32 index = ui->comboBox->currentIndex();
    if (index != 0) {
        QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save Route"), QDir::homePath(), tr("Gpx Files (*.gpx)"));

        if (fileName.isEmpty()) {
            return;
        } else {
            QFileInfo fileInfo(fileName);
            if (fileInfo.exists()) {
                QMessageBox::warning(this, tr("Warning"),
                                     QString("File %1 already exists").arg(fileName), QMessageBox::Ok);
                return;
            }

            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("Warning"),
                                     QString("Can't open file %1").arg(fileName), QMessageBox::Ok);
                return;
            }

            auto rwFuncs = getRWFunctions(fileInfo.completeSuffix());
            rwFuncs.second(file, RuntimeStorage::instance().getRoute(ui->comboBox->currentIndex() - 1));
        }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(qint32 index)
{
    if (index == 0) {
        m_coordinatesPresenter->setCurrentRouteIndex(-1);
        m_coordinatesPresenter->clear();
        return;
    }

    m_coordinatesPresenter->setCurrentRouteIndex(index - 1);
    emit m_coordinatesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_actionDelete_triggered()
{
    qint32 index = ui->comboBox->currentIndex();
    if (index == 0) {
        return;
    }

    QSharedPointer<Route> route = RuntimeStorage::instance().getRoute(index - 1);
    auto redoFunc = std::bind(&MainWindow::removeRoute, this, index - 1);
    auto undoFunc = std::bind(&MainWindow::addRoute, this, std::placeholders::_1, index - 1);
    m_undoStack->push(new RemoveRouteCommand(route, redoFunc, undoFunc));
}

void MainWindow::on_addCoordinateButton_clicked()
{
    if (ui->comboBox->currentIndex() == 0) {
        return;
    }

    m_addCoordinateDialog->setMaxPosition(RuntimeStorage::instance().getRoute(
            ui->comboBox->currentIndex() - 1)->getPath().count());
    m_addCoordinateDialog->show();
}

void MainWindow::on_removeCoordinateButton_clicked()
{
    auto rows = ui->coordinatesView->selectionModel()->selectedRows();
    qint32 routeIndex = ui->comboBox->currentIndex();
    qint32 coordinateIndex = rows.first().row();

    for (auto &row : rows) {
        Coordinate coordinate;

        for (auto j = 0; j < 3; ++j) {
            QModelIndex index = m_coordinatesPresenter->index(row.row(), j);
            qreal value = m_coordinatesPresenter->data(index, Qt::DisplayRole).toDouble();

            switch (j) {
            case 0:
                coordinate.setLatitude(value);
                break;
            case 1:
                coordinate.setLongitude(value);
                break;
            case 2:
                coordinate.setAltitude(value);
                break;
            default:
                break;
            }
        }

        auto redoFunc = std::bind(&MainWindow::removeCoordinate,
                                  this, routeIndex - 1, coordinateIndex);
        auto undoFunc = std::bind(&MainWindow::addCoordinate,
                                  this, std::placeholders::_1, routeIndex - 1, coordinateIndex);
        m_undoStack->push(new RemoveCoordinateCommand(coordinate, redoFunc, undoFunc));
    }
}

void MainWindow::updateComboBox(qint32 index, const QString &value)
{
    ui->comboBox->setItemText(index + 1, QString("%1. %2").arg(index + 1).arg(value));
}

void MainWindow::recieveCoordinate(qint32 position, const Coordinate &coordinate)
{
    auto redoFunc = std::bind(&MainWindow::addCoordinate,
                              this, std::placeholders::_1, ui->comboBox->currentIndex() - 1, position);
    auto undoFunc = std::bind(&MainWindow::removeCoordinate,
                              this, ui->comboBox->currentIndex() - 1, position);
    m_undoStack->push(new AddCoordinateCommand(coordinate, redoFunc, undoFunc));
}

void MainWindow::coordinateChanged(qint32 index, const Coordinate &oldCoordinate, const Coordinate newCoordinate)
{
    auto undoRedoFunc = std::bind(&MainWindow::updateCoordinate,
                                  this, std::placeholders::_1, ui->comboBox->currentIndex() - 1, index);
    m_undoStack->push(new UpdateCoordinateCommand(oldCoordinate, newCoordinate, undoRedoFunc));
}

void MainWindow::addRoute(QSharedPointer<Route> route, qint32 index)
{
    RuntimeStorage::instance().addRoute(index, route);
    ui->comboBox->insertItem(index + 1, QString("%1. %2").arg(index + 1).arg(route->getName()));
    emit m_routesPresenter->layoutChanged();
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::removeRoute(qint32 index)
{
    ui->comboBox->removeItem(index + 1);
    RuntimeStorage::instance().removeRoute(index);
    emit m_routesPresenter->layoutChanged();
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::addCoordinate(const Coordinate &coordinate, qint32 routeIndex, qint32 coordinateIndex)
{
    RuntimeStorage::instance().getRoute(routeIndex)->addCoordinate(coordinateIndex, coordinate);
    emit m_coordinatesPresenter->layoutChanged();
    emit m_routesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateCoordinate(const Coordinate &coordinate, qint32 routeIndex, qint32 coordinateIndex)
{
    RuntimeStorage::instance().getRoute(routeIndex)->updateCoordinate(coordinateIndex, coordinate);
    emit m_coordinatesPresenter->layoutChanged();
    emit m_routesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::removeCoordinate(qint32 routeIndex, qint32 coordinateIndex)
{
    RuntimeStorage::instance().getRoute(routeIndex)->removeCoordinate(coordinateIndex);
    emit m_coordinatesPresenter->layoutChanged();
    emit m_routesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
