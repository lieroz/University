/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
	public:
		QAction* actionLoad;
		QAction* actionHelp;
		QWidget* centralWidget;
		QHBoxLayout* horizontalLayout;
		QGraphicsView* graphicsView;
		QStatusBar* statusBar;
		QToolBar* MenuToolBar;
		
		void setupUi(QMainWindow* MainWindow) {
			if (MainWindow->objectName().isEmpty()) {
				MainWindow->setObjectName(QStringLiteral("MainWindow"));
			}
			MainWindow->resize(780, 613);
			actionLoad = new QAction(MainWindow);
			actionLoad->setObjectName(QStringLiteral("actionLoad"));
			actionLoad->setCheckable(true);
			actionHelp = new QAction(MainWindow);
			actionHelp->setObjectName(QStringLiteral("actionHelp"));
			actionHelp->setCheckable(true);
			centralWidget = new QWidget(MainWindow);
			centralWidget->setObjectName(QStringLiteral("centralWidget"));
			horizontalLayout = new QHBoxLayout(centralWidget);
			horizontalLayout->setSpacing(6);
			horizontalLayout->setContentsMargins(11, 11, 11, 11);
			horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
			graphicsView = new QGraphicsView(centralWidget);
			graphicsView->setObjectName(QStringLiteral("graphicsView"));
			graphicsView->setEnabled(true);
			graphicsView->setFocusPolicy(Qt::NoFocus);
			graphicsView->setInteractive(false);
			
			horizontalLayout->addWidget(graphicsView);
			
			MainWindow->setCentralWidget(centralWidget);
			statusBar = new QStatusBar(MainWindow);
			statusBar->setObjectName(QStringLiteral("statusBar"));
			MainWindow->setStatusBar(statusBar);
			MenuToolBar = new QToolBar(MainWindow);
			MenuToolBar->setObjectName(QStringLiteral("MenuToolBar"));
			MainWindow->addToolBar(Qt::TopToolBarArea, MenuToolBar);
			
			MenuToolBar->addAction(actionLoad);
			MenuToolBar->addAction(actionHelp);
			
			retranslateUi(MainWindow);
			
			QMetaObject::connectSlotsByName(MainWindow);
		} // setupUi
		
		void retranslateUi(QMainWindow* MainWindow) {
			MainWindow->setWindowTitle(QApplication::translate("MainWindow", "3D - viewer", 0));
			actionLoad->setText(QApplication::translate("MainWindow",
			                                            "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273",
			                                            0));
#ifndef QT_NO_TOOLTIP
			actionLoad->setToolTip(QApplication::translate("MainWindow",
			                                               "<html><head/><body><p>\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \321\204\320\260\320\271\320\273\320\260 \321\201 3D-\320\274\320\276\320\264\320\265\320\273\321\214\321\216</p></body></html>",
			                                               0));
#endif // QT_NO_TOOLTIP
			actionLoad->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0));
			actionHelp->setText(
					QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260",
					                        0));
#ifndef QT_NO_TOOLTIP
			actionHelp->setToolTip(QApplication::translate("MainWindow",
			                                               "\320\241\320\277\321\200\320\260\320\262\320\272\320\260 \320\277\320\276 \321\200\320\260\320\261\320\276\321\202\320\265 \321\201 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271",
			                                               0));
#endif // QT_NO_TOOLTIP
			actionHelp->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0));
			MenuToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
		} // retranslateUi
	
};

namespace Ui {
	class MainWindow : public Ui_MainWindow { };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
