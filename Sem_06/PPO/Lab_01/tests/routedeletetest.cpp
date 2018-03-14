#include <routedeletetest.h>

#include <QThreadPool>

void RouteDeleteTest::testRouteDeleteSequential()
{
    for (int i = 0; i < 10; ++i) {
        QSharedPointer<Route> route(new Route);
        RouteStore::instance()->addRoute(route);
    }

    QCOMPARE(RouteStore::instance()->size(), 10);

    for (int i = 0; i < 10; ++i) {
        RouteStore::instance()->deleteRoute(9 - i);
    }

    QCOMPARE(RouteStore::instance()->size(), 0);
}

class Task : public QRunnable
{
public:
    Task(std::function<void()> foo) : m_foo(foo) {}

protected:
    void run() override
    {
        m_foo();
    }

private:
    std::function<void()> m_foo;
};

void RouteDeleteTest::testRouteDeleteMultithreaded()
{
    QThreadPool pool;
    pool.setMaxThreadCount(10);

    for (int i = 0; i < 1000; ++i) {
        Task *task = new Task([]() {
            QSharedPointer<Route> route(new Route);
            RouteStore::instance()->addRoute(route);
        });
        task->setAutoDelete(true);
        pool.start(task);
    }

    pool.waitForDone();
    QCOMPARE(RouteStore::instance()->size(), 1000);

    for (int i = 0; i < 1000; ++i) {
        RouteStore::instance()->deleteRoute(999 - i);
    }

    QCOMPARE(RouteStore::instance()->size(), 0);
}

QTEST_MAIN(RouteDeleteTest)
#include "routedeletetest.moc"
