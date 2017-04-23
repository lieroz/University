#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>

#include "facade/facade.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

        const double ANGLE = 3 * M_PI / 180;
        const double OFFSET = 5;
        const double SCALE_FACTOR = 2;

        static size_t model_count;
        static size_t camera_count;

    public:
        explicit MainWindow(QWidget* parent = 0);
        virtual ~MainWindow();

    protected:
        virtual void keyPressEvent(QKeyEvent*) override;

        void set_up_scene_view();
        void set_up_model_view();

        void update_scene_view();
        void update_model_view();

private slots:
        void on_actionupload_model_triggered();

        void on_addSceneObjectButton_clicked();

        void on_removeSceneObjectButton_clicked();

        void on_deleteViewButton_clicked();

private:
        Ui::MainWindow* ui;
        QGraphicsScene* scene_view_scene;
        QGraphicsScene* model_view_scene;

        facade command_controller;
};

#endif // MAINWINDOW_HPP
