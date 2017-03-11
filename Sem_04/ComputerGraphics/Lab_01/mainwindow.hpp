#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTableWidget>
#include <QScrollBar>
#include <QVector>

#include "dimensionsetter.hpp"
#include "drawer.hpp"
#include "solver.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

        const int WINDOW_HEIGHT = 700;
        const int WINDOW_WIDTH = 1400;
        const int COLUMN_COUNT = 2;

    public:
        explicit MainWindow(QWidget* parent = 0);

        virtual ~MainWindow();

    private slots:
        void on_leftAddButton_clicked();
        void on_leftDeleteButton_clicked();

        void on_rightAddButton_clicked();
        void on_rightDeleteButton_clicked();

        void on_drawButton_clicked();
        void on_solveButton_clicked();

    private:
        int canvas_width;
        int canvas_height;

        Ui::MainWindow* ui;
        QGraphicsScene* scene;

        void setUpTables();
        void setUpCanvas();

        static void fillVector(QVector<QPoint>&, QTableWidget*);
};

#endif // MAINWINDOW_HPP
