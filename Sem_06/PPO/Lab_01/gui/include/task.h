#pragma once

#include <QRunnable>
#include <functional>

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
