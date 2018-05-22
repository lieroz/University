//
// Created by lieroz on 14.05.18.
//

#include <ui/AddCoordinateDialog.h>
#include "ui_AddCoordinateDialog.h"

AddCoordinateDialog::AddCoordinateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCoordinateDialog)
{
    ui->setupUi(this);
    setFixedSize(QSize(250, 150));

    ui->latitudeSpinBox->setMinimum(-90.0);
    ui->latitudeSpinBox->setMaximum(90.0);
    ui->latitudeSpinBox->setDecimals(7);

    ui->longitudeSpinBox->setMinimum(-180.0);
    ui->longitudeSpinBox->setMaximum(180.0);
    ui->longitudeSpinBox->setDecimals(7);

    ui->altitudeSpinBox->setMinimum(-5000.0);
    ui->altitudeSpinBox->setMaximum(5000.0);
    ui->altitudeSpinBox->setDecimals(7);

    ui->positionSpinBox->setMinimum(0);
}

AddCoordinateDialog::~AddCoordinateDialog()
{
    delete ui;
}

void AddCoordinateDialog::setMaxPosition(qint32 position)
{
    ui->positionSpinBox->setMaximum(position);
    ui->positionSpinBox->setValue(position);
}

void AddCoordinateDialog::on_okButton_clicked()
{
    Coordinate coordinate(ui->latitudeSpinBox->value(),
                          ui->longitudeSpinBox->value(), ui->altitudeSpinBox->value());
    emit sendCoordinate(ui->positionSpinBox->value(), coordinate);
    close();
}
