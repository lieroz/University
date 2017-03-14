#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QMessageBox>
#include <cmath>

#include "point2d.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

        const int WINDOW_HEIGHT = 732;
        const int WINDOW_WIDTH = 960;
        const int SIDE = 100;
        const int RADIUS = 2;
        const double STEP = 0.01;

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    protected:
        virtual void keyPressEvent(QKeyEvent*) override;

        void setUpView();
        void setUpScene();

        void setUpRotation(double);
        void draw();

private slots:
        void on_action_triggered();

private:
        double x_center;
        double y_center;

        double x_scale_point;
        double y_scale_point;
        double x_scale_coef;
        double y_scale_coef;

        double x_offset_point;
        double y_offset_point;

        double x_rotation_point;
        double y_rotation_point;
        double angle = 5;

        Ui::MainWindow* ui;
        QGraphicsScene* scene;
        QVector<Point2D> points;
};

#endif // MAINWINDOW_HPP
