//
// Created by lieroz on 22.05.18.
//

#include <QAction>
#include <QComboBox>
#include <QDebug>

#include <data/RuntimeStorage.h>

#include <RouteTest.h>

RouteTest::RouteTest(QObject *parent)
    : QObject(parent)
{
}

void RouteTest::testCreateRoute()
{
    QAction *action = window.findChild<QAction *>("actionNew");
    QVERIFY(action != nullptr);
    emit action->triggered();
    QVERIFY(RuntimeStorage::instance().count() != 0);
}

void RouteTest::testRemoveRoute()
{
    QComboBox *box = window.findChild<QComboBox *>("comboBox");
    box->setCurrentIndex(1);
    QAction *action = window.findChild<QAction *>("actionDelete");
    QVERIFY(action != nullptr);
    emit action->triggered();
    QVERIFY(RuntimeStorage::instance().count() == 0);
}

QTEST_MAIN(RouteTest)
#include "RouteTest.moc"
