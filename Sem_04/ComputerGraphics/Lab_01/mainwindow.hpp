#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <QVector>
#include <regex>

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
        const int ROW_COUNT = 4;
        const double SCALE_FACTOR = 0.95;

    public:
        explicit MainWindow(QWidget* parent = 0);
        virtual ~MainWindow();

    private slots:
        void on_action_triggered();

        void on_leftAddButton_clicked();
        void on_leftDeleteButton_clicked();

        void on_rightAddButton_clicked();
        void on_rightDeleteButton_clicked();

        void on_drawButton_clicked();
        void on_solveButton_clicked();
        void on_drawSolutionButton_clicked();

    private:
        int canvas_width;
        int canvas_height;

        Ui::MainWindow* ui;
        QGraphicsScene* scene;
        std::regex is_number{"^(([0-9]*)|(([0-9]*).([0-9]*)))$"};

        void setUpTables();
        void setUpAnswerTables();
        void setUpCanvas();

        void fillVector(QVector<Point2D>&, QTableWidget*);
};

#endif // MAINWINDOW_HPP
