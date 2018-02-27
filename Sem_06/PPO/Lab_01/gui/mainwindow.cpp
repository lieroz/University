#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl(QStringLiteral("qrc:/gui/resources/qml/MapView.qml")));
    ui->tabWidget->addTab(container, "MapView");
}

MainWindow::~MainWindow()
{
    delete ui;
}
