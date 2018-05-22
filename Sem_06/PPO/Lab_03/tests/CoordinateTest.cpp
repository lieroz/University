//
// Created by lieroz on 22.05.18.
//

#include <QComboBox>
#include <QPushButton>
#include <QAction>
#include <QTableView>

#include <data/RuntimeStorage.h>
#include <ui/AddCoordinateDialog.h>

#include <CoordinateTest.h>

CoordinateTest::CoordinateTest(QObject *parent)
    : QObject(parent)
{
}

void CoordinateTest::initTestCase()
{
    QAction *action = window.findChild<QAction *>("actionNew");
    QVERIFY(action != nullptr);
    emit action->triggered();
    QVERIFY(RuntimeStorage::instance().count() != 0);
    QComboBox *box = window.findChild<QComboBox *>("comboBox");
    QVERIFY(box != nullptr);
    box->setCurrentIndex(1);
}

void CoordinateTest::testAddCoordinate()
{
    QPushButton *button = window.findChild<QPushButton *>("addCoordinateButton");
    QVERIFY(button != nullptr);
    emit button->click();
    AddCoordinateDialog *dialog = window.findChild<AddCoordinateDialog *>("m_addCoordinateDialog");
    QVERIFY(dialog != nullptr);
    QPushButton *dialogButton = dialog->findChild<QPushButton *>("okButton");
    QVERIFY(dialogButton != nullptr);
    emit dialogButton->click();
    QVERIFY(RuntimeStorage::instance().getRoute(0)->getPath().count() != 0);
}

void CoordinateTest::testUpdateCoordinate()
{
    QTableView *view = window.findChild<QTableView *>("coordinatesView");
    QVERIFY(view != nullptr);
    QModelIndex index  = view->model()->index(0, 0);
    view->model()->setData(index, 34);
    QCOMPARE(RuntimeStorage::instance().getRoute(0)->getCoordinate(0)->getLatitude(), 34);
}

void CoordinateTest::testRemoveCoordinate()
{
    QPushButton *button = window.findChild<QPushButton *>("removeCoordinateButton");
    QVERIFY(button != nullptr);
    QTableView *view = window.findChild<QTableView *>("coordinatesView");
    QVERIFY(view != nullptr);
    view->selectRow(0);
    emit button->click();
    QVERIFY(RuntimeStorage::instance().getRoute(0)->getPath().count() == 0);
}

void CoordinateTest::cleanUpTestCase()
{
    QAction *action = window.findChild<QAction *>("actionDelete");
    QVERIFY(action != nullptr);
    emit action->triggered();
    QVERIFY(RuntimeStorage::instance().count() == 0);
}

QTEST_MAIN(CoordinateTest)
#include "CoordinateTest.moc"
