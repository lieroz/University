#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
	ui->setupUi(this);
	scene = new QGraphicsScene(10, 10, ui->graphicsView->width() - 10, ui->graphicsView->height() - 10);
	
}

MainWindow::~MainWindow() {
	argument act;
	processor(&act, CLEAR);
	delete ui;
}

QString MainWindow::get_name_file() {
	return QFileDialog::getOpenFileName(0, QObject::tr("Укажите файл с моделью"), QDir::currentPath(),
	                                    QObject::tr("Все файлы (*.txt)"));
}

void MainWindow::on_actionLoad_triggered() {
	QString dir = get_name_file();
	
	if (dir != "") {
		argument act;
		act.load_act = QStringToCharArr(dir);
		errs_num err = processor(&act, LOAD);
		ErrorMessage(this, (errs_num) err);
		
		if (err != NO_ERR) {
			return;
		}
		
		act.draw_act.height = static_cast<int>(scene->height());
		act.draw_act.width = static_cast<int>(scene->width());
		act.draw_act.scene = scene;
		err = processor(&act, DRAW);
		ErrorMessage(this, (errs_num) err);
		
		if (err != NO_ERR) {
			return;
		
		} else {
			ui->statusBar->showMessage("Загружен файл : " + dir);
			ui->graphicsView->setScene(scene);
		}
	
	} else {
		ErrorMessage(this, ERR_WITH_FILE);
	}
}

void MainWindow::on_actionHelp_triggered() {
	QString help_s;
	help_s = "Перед началом работы загрузите файл\n"
			"\n\nУправление изображением:\n"
			"↑\tПеремещение вверх\n"
			"↓\tПеремещение вниз\n"
			"→\tПеремещение вправо\n"
			"←\tПеремещение влево\n"
			"+\tУвеличение\n"
			"-\tУменьшение\n"
			"W\tПоворот вверх\n"
			"S\tПоворот вниз\n"
			"A\tПоворот влево\n"
			"D\tПоворот вправо\n";
	QMessageBox::information(this, "Справка", help_s);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	argument act;
	Zero_change(&(act.modi_act));
	int key = event->key();
	
	switch (key) {
		
		case Qt::Key_Up: {
			act.modi_act.moveOY += 5;
			break;
		}
		
		case Qt::Key_Down: {
			act.modi_act.moveOY -= 5;
			break;
		}
		
		case Qt::Key_Left: {
			act.modi_act.moveOX -= 5;
			break;
		}
		
		case Qt::Key_Right: {
			act.modi_act.moveOX += 5;
			break;
		}
		
		case Qt::Key_Plus: {
			act.modi_act.scale *= 1.5;
			break;
		}
		
		case Qt::Key_Minus: {
			act.modi_act.scale *= 0.5;
			break;
		}
		
		case Qt::Key_W: {
			act.modi_act.angleOX -= 5;
			break;
		}
		
		case Qt::Key_S: {
			act.modi_act.angleOX += 5;
			break;
		}
		
		case Qt::Key_D: {
			act.modi_act.angleOY -= 5;
			break;
		}
		
		case Qt::Key_A: {
			act.modi_act.angleOY += 5;
			break;
		}
		
		default:
			return;
	}
	
	errs_num err = processor(&act, CHANGE);
	act.draw_act.height = static_cast<int>(scene->height());
	act.draw_act.width = static_cast<int>(scene->width());
	act.draw_act.scene = scene;
	err = processor(&act, DRAW);
	ErrorMessage(this, (errs_num) err);
	
	if (err == NO_ERR) {
		ui->graphicsView->setScene(scene);
	
	} else {
		return;
	}
}
