//
// Created by lieroz on 22.05.18.
//

#include <QAction>
#include <QComboBox>
#include <QFileDialog>

#include <data/RuntimeStorage.h>

#include <LoadDataTest.h>

LoadDataTest::LoadDataTest(QObject *parent)
    : QObject(parent)
{
}

void LoadDataTest::testLoadRouteFromGpx()
{
    QFileDialog *dialog = window.findChild<QFileDialog *>("m_fileDialog");
    QVERIFY(dialog != nullptr);
    QStringList list = {"test.gpx"};
    emit dialog->filesSelected(list);
    emit dialog->accepted();
    QVERIFY(RuntimeStorage::instance().count() != 0);
    QComboBox *box = window.findChild<QComboBox *>("comboBox");
    QVERIFY(box != nullptr);
    box->setCurrentIndex(1);
    QAction *action = window.findChild<QAction *>("actionDelete");
    QVERIFY(action != nullptr);
    emit action->triggered();
    QVERIFY(RuntimeStorage::instance().count() == 0);
}

void LoadDataTest::testLoadRouteFromPolyline()
{
    QFileDialog *dialog = window.findChild<QFileDialog *>("m_fileDialog");
    QVERIFY(dialog != nullptr);
    QStringList list = {"test.txt"};
    emit dialog->filesSelected(list);
    emit dialog->accepted();
    QVERIFY(RuntimeStorage::instance().count() != 0);
    QComboBox *box = window.findChild<QComboBox *>("comboBox");
    QVERIFY(box != nullptr);
    box->setCurrentIndex(1);
    QAction *action = window.findChild<QAction *>("actionDelete");
    QVERIFY(action != nullptr);
    emit action->triggered();
    QVERIFY(RuntimeStorage::instance().count() == 0);
}

QTEST_MAIN(LoadDataTest)
#include "LoadDataTest.moc"
