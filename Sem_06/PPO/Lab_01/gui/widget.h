#pragma once

#include <QWidget>
#include <QScopedPointer>

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

Q_SIGNALS:
    void sendToMainWindow(QString text);

private Q_SLOTS:
    void oKButtonClicked();

private:
    QScopedPointer<Ui::Widget> ui;
};
