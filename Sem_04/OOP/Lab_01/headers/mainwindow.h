#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QString>
#include <QKeyEvent>

#include "error.h"
#include "geometry.h"
#include "load_file.h"
#include "qstrtochararr.h"
#include "print_picture.h"
#include "processor.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
	
	private:
		Ui::MainWindow* ui;
		QGraphicsScene* scene;
		QString get_name_file();
	
	public:
		explicit MainWindow(QWidget* parent = 0);
		virtual ~MainWindow();
	
	private slots:
		void on_actionLoad_triggered();
		
		void on_actionHelp_triggered();
	
	protected:
		virtual void keyPressEvent(QKeyEvent* event);
	
};

#endif // MAINWINDOW_H
