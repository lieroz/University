#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        virtual ~MainWindow();

    protected:
        virtual void keyPressEvent(QKeyEvent*) override;

    private:
        Ui::MainWindow* ui;
};

#endif // MAINWINDOW_HPP
