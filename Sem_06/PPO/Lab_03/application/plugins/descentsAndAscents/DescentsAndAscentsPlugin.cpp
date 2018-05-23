//
// Created by lieroz on 23.05.18.
//

#include <DescentsAndAscentsPlugin.h>

DescentsAndAscentsPlugin::DescentsAndAscentsPlugin(QWidget *parent)
    : QWidget(parent)
{
}

QString DescentsAndAscentsPlugin::name()
{
    return "DescentsAndAscentsPlugin";
}

void DescentsAndAscentsPlugin::exec(QSharedPointer<Route> route)
{

}

bool DescentsAndAscentsPlugin::isRunning()
{
    return isVisible();
}
