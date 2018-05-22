//
// Created by lieroz on 14.05.18.
//

#ifndef ADDCOORDINATEDIALOG_H
#define ADDCOORDINATEDIALOG_H

#include <QDialog>

#include <data/models/Coordinate.h>

namespace Ui
{
    class AddCoordinateDialog;
}

class AddCoordinateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCoordinateDialog(QWidget *parent = 0);
    ~AddCoordinateDialog();

    void setMaxPosition(qint32 position);

private slots:
    void on_okButton_clicked();

Q_SIGNALS:
    void sendCoordinate(qint32, const Coordinate &coordinate);

private:
    Ui::AddCoordinateDialog *ui;
};

#endif // ADDCOORDINATEDIALOG_H
