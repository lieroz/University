//
// Created by lieroz on 13.05.18.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoStack>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include <ui/presenters/RoutesPresenter.h>
#include <ui/presenters/CoordinatesPresenter.h>
#include <data/models/Route.h>
#include <ui/AddCoordinateDialog.h>
#include <ui/presenters/SpinBoxDelegate.h>

#include <../plugins/PluginInterface.h>

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

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionDelete_triggered();

    void on_comboBox_currentIndexChanged(qint32 index);

    void on_addCoordinateButton_clicked();
    void on_removeCoordinateButton_clicked();

    void updateComboBox(qint32 index, const QString &value);
    void recieveCoordinate(qint32 position, const Coordinate &coordinate);
    void coordinateChanged(qint32 index, const Coordinate &oldCoordinate, const Coordinate newCoordinate);

    void appAboutToQuit();
    void filesSelected(const QStringList& fileNames);
    void accepted();
    void executePlugin(QAction *action);

private:
    void prepareAppContext();
    void saveFile();
    void loadPlugins();

    void addRoute(QSharedPointer<Route> route, qint32 index);
    void removeRoute(qint32 index);

    void addCoordinate(const Coordinate &point, qint32 routeIndex, qint32 pointIndex);
    void updateCoordinate(const Coordinate &point, qint32 routeIndex, qint32 pointIndex);
    void removeCoordinate(qint32 routeIndex, qint32 pointIndex);

private:
    Ui::MainWindow *ui;
    RoutesPresenter *m_routesPresenter;
    CoordinatesPresenter *m_coordinatesPresenter;
    QUndoStack *m_undoStack;
    AddCoordinateDialog *m_addCoordinateDialog;
    SpinBoxDelegate *m_delegate;
    QFileDialog *m_fileDialog;
    QStringList m_fileNames;
    QVector<QSharedPointer<PluginInterface>> m_plugins;
};

#endif // MAINWINDOW_H
