#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QColorDialog>
#include <QResizeEvent>
#include <QMessageBox>
#include <cmath>
#include <functional>

#include "objectwrapper.hpp"
#include "timer.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

        const int FRAME_SIZE = 310;

    public:
        explicit MainWindow(QWidget* parent = 0);
        virtual ~MainWindow();

    protected:
        virtual void resizeEvent(QResizeEvent*) override;

    private slots:
        void on_lineColorButton_clicked();
        void on_drawButton_clicked();
        void on_timeButton_clicked();
        void on_cleanButton_clicked();

        void mousePosition();
        void mousePressed();
        void mouseLeft();

    private:
        void setUpSpinBorders();
        void drawLine(Algorithms::algorithm, QLineF, QColor);
        void drawStar(Algorithms::algorithm, QLineF, QColor);
        void measureTime(Timer&, QString&, QLineF&, std::function<void(Algorithms::algorithm, QLineF, QColor)>&);

        Ui::MainWindow* ui;
        QColor line_color = Qt::black;
        QGraphicsScene* scene;
        QPixmap* pixmap;

        QVector<LineWrapper> scene_lines;
        QVector<LineWrapper> scene_stars;
};

#endif // MAINWINDOW_HPP
