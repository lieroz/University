//
// Created by lieroz on 15.05.18.
//

#include <QDoubleSpinBox>

#include <ui/presenters/SpinBoxDelegate.h>
#include <QDebug>

SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setDecimals(7);

    switch (index.column()) {
    case 0:
        editor->setMinimum(-90.0);
        editor->setMaximum(90.0);
        break;
    case 1:
        editor->setMinimum(-180.0);
        editor->setMaximum(180.0);
        break;
    case 2:
        editor->setMinimum(-5000.0);
        editor->setMaximum(5000.0);
        break;
    default:
        break;
    }
    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qreal value = index.model()->data(index).toDouble();
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
    spinbox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
    spinbox->interpretText();
    qreal value = spinbox->value();
    model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
