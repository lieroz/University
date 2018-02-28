#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    ui.reset(new Ui::Widget);
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(oKButtonClicked()));
}

Widget::~Widget()
{

}

void Widget::oKButtonClicked()
{
    emit sendToMainWindow(ui->textEdit->document()->toPlainText());
    close();
}
