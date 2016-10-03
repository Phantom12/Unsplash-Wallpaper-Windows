#ifndef UNSPLASH_GUI_H
#define UNSPLASH_GUI_H

#include <QtWidgets/QMainWindow>
#include "ui_unsplash_gui.h"
#include "Unsplash_Wei.h"
#include <thread>
#include "qsystemtrayicon.h"
#include <QtGui\QCloseEvent>

class Unsplash_GUI : public QMainWindow, public unsplash::Unsplash_Wei
{
	Q_OBJECT

public:
	Unsplash_GUI(QWidget *parent = 0);
	~Unsplash_GUI();

public slots:
	void on_Refresh_clicked();
	void on_Res_changed();
	void on_Interval_changed();
	void on_defaultSave_clicked();
	void on_changeSave_clicked();
	void on_exit_clicked();
	void on_About_clicked();

//protected:
//	void closeEvent(QCloseEvent* e); //overwrite the close button to minimize the window instead

private:
	Ui::Unsplash_GUIClass ui;
	int intervalComboboxLastIdx; //in case the user cancel on the add custom interval action, revert back to showing the last interval selection
	std::thread loopExecThread;
	QSystemTrayIcon* trayObj;
	QMenu* trayObjMenu;
	QAction* exitAct;
	QAction* settingAct;

private slots:
	void trayMenuActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // UNSPLASH_GUI_H
