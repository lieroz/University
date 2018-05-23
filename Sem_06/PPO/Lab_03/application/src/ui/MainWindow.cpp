//
// Created by lieroz on 13.05.18.
//

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPluginLoader>
#include <QDebug>

#include <data/DataRW.h>
#include <data/RuntimeStorage.h>
#include <data/Polyline.h>

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

    QStringList routesViewHeaders = {"Name", "Length (km)", "Created"};
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
    m_addCoordinateDialog->setObjectName("m_addCoordinateDialog");
    connect(m_addCoordinateDialog, SIGNAL(sendCoordinate(qint32, Coordinate)),
            this, SLOT(recieveCoordinate(qint32, Coordinate)));

    prepareAppContext();
    connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(appAboutToQuit()));

    m_fileDialog = new QFileDialog(this, tr("File Dialog"), QDir::homePath(), tr("All Files (*)"));
    m_fileDialog->setObjectName("m_fileDialog");
    m_fileDialog->setFileMode(QFileDialog::ExistingFiles);
    connect(m_fileDialog, SIGNAL(filesSelected(QStringList)), this, SLOT(filesSelected(QStringList)));
    connect(m_fileDialog, SIGNAL(accepted()), this, SLOT(accepted()));

    loadPlugins();
    connect(ui->menuPlugins, SIGNAL(triggered(QAction *)), this, SLOT(executePlugin(QAction *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    m_fileDialog->exec();
}

void MainWindow::on_actionSave_triggered()
{
    saveFile();
}

void MainWindow::on_actionNew_triggered()
{
    Route route;
    qint32 index = RuntimeStorage::instance().count();

    auto redoFunc = std::bind(&MainWindow::addRoute, this, std::placeholders::_1, index);
    auto undoFunc = std::bind(&MainWindow::removeRoute, this, index);
    m_undoStack->push(new AddRouteCommand(QSharedPointer<Route>::create(route), redoFunc, undoFunc));
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

void MainWindow::on_comboBox_currentIndexChanged(qint32 index)
{
    if (index == 0) {
        m_coordinatesPresenter->setCurrentRouteIndex(-1);
        m_coordinatesPresenter->clear();
        ui->chartView->setData(QSharedPointer<Route>::create(Route()));
        return;
    }

    m_coordinatesPresenter->setCurrentRouteIndex(index - 1);
    emit m_coordinatesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->chartView->setData(RuntimeStorage::instance().getRoute(index - 1));
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
    if (routeIndex == 0 || rows.isEmpty()) {
        return;
    }

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

void MainWindow::appAboutToQuit()
{
    QDir dir(QDir::currentPath() + "/appcontext");
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);

    for (const auto &dirFile : dir.entryList()) {
        dir.remove(dirFile);
    }

    quint32 fileName = 0;
    for (auto route : RuntimeStorage::instance().getAll()) {
        QFile file(QString("%1/%2.gpx").arg(dir.absolutePath()).arg(QString::number(++fileName)));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return;
        }

        auto rwFuncs = getRWFunctions("gpx");
        rwFuncs.second(file, route);
    }
}

void MainWindow::filesSelected(const QStringList &fileNames)
{
    m_fileNames = fileNames;
}

void MainWindow::accepted()
{
    for (const auto &fileName : m_fileNames) {
        QFileInfo fileInfo(fileName);
        auto rwFuncs = getRWFunctions(fileInfo.completeSuffix());
        QSharedPointer<Route> route = rwFuncs.first(fileName);
        qint32 index = RuntimeStorage::instance().count();

        auto redoFunc = std::bind(&MainWindow::addRoute, this, std::placeholders::_1, index);
        auto undoFunc = std::bind(&MainWindow::removeRoute, this, index);
        m_undoStack->push(new AddRouteCommand(route, redoFunc, undoFunc));
    }
}

void MainWindow::executePlugin(QAction *action)
{
    qint32 index = ui->comboBox->currentIndex();
    if (index == 0) {
        return;
    }

    auto actions = ui->menuPlugins->actions();
    for (auto i = 0; i < actions.count(); ++i) {
        if (actions[i] == action && !m_plugins[i]->isRunning()) {
            m_plugins[i]->exec(RuntimeStorage::instance().getRoute(index - 1));
            return;
        }
    }
}

void MainWindow::prepareAppContext()
{
    QDir dir(QDir::currentPath());
    dir.mkdir("appcontext");
    dir.cd("appcontext");

    for (auto fileInfo : dir.entryInfoList()) {
        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..") {
            continue;
        }

        auto rwFuncs = getRWFunctions(fileInfo.completeSuffix());
        auto route = rwFuncs.first(fileInfo.absoluteFilePath());
        qint32 index = RuntimeStorage::instance().count();

        auto redoFunc = std::bind(&MainWindow::addRoute, this, std::placeholders::_1, index);
        auto undoFunc = std::bind(&MainWindow::removeRoute, this, index);
        m_undoStack->push(new AddRouteCommand(route, redoFunc, undoFunc));
    }
}

void MainWindow::saveFile()
{
    qint32 index = ui->comboBox->currentIndex();
    if (index != 0) {
        QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save Polyline"), QDir::homePath(), tr("All Files (*)"));

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
            rwFuncs.second(file, RuntimeStorage::instance().getRoute(index));
        }
    }
}

void MainWindow::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    for (QString fileName : pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();

        if (plugin) {
            QSharedPointer<PluginInterface> pointer(qobject_cast<PluginInterface *>(plugin));
            QAction *action = new QAction(pointer->name(), this);
            ui->menuPlugins->addAction(action);
            m_plugins.append(pointer);
        }
    }
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
    auto route = RuntimeStorage::instance().getRoute(routeIndex);
    route->addCoordinate(coordinateIndex, coordinate);
    emit m_coordinatesPresenter->layoutChanged();
    emit m_routesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->chartView->setData(route);
}

void MainWindow::updateCoordinate(const Coordinate &coordinate, qint32 routeIndex, qint32 coordinateIndex)
{
    auto route = RuntimeStorage::instance().getRoute(routeIndex);
    route->updateCoordinate(coordinateIndex, coordinate);
    emit m_coordinatesPresenter->layoutChanged();
    emit m_routesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->chartView->setData(route);
}

void MainWindow::removeCoordinate(qint32 routeIndex, qint32 coordinateIndex)
{
    auto route = RuntimeStorage::instance().getRoute(routeIndex);
    route->removeCoordinate(coordinateIndex);
    emit m_coordinatesPresenter->layoutChanged();
    emit m_routesPresenter->layoutChanged();
    ui->coordinatesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->routesView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->chartView->setData(route);
}
