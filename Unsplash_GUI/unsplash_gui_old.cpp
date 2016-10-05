#include "unsplash_gui_old.h"
#include "qfiledialog.h"
#include <thread>
#include "QtConcurrent\qtconcurrentrun.h"
#include "addcustominterval.h"
#include <fstream>
#include "aboutdialog.h"
#include "qmessagebox.h"

//Unless otherwise specified, the constructors of a derived class calls the default constructor of its base classes
Unsplash_GUI_old::Unsplash_GUI_old(QWidget *parent)
	: QMainWindow(parent)
{
	QIcon icon(":/image/minecart_cropped.ico");
	this->setWindowIcon(icon);

	ui.setupUi(this);
	ui.resComboBox->setCurrentText("Auto");
	ui.intervalComboBox->setCurrentText("1 hour");
	ui.saveFolderDisp->setText(picFolderDir.c_str());
	intervalComboboxLastIdx = ui.intervalComboBox->currentIndex();
	if (IsWindows8OrGreater()) //consistent with the definition of differentWallpaperPerMonitor in Unsplash_Wei_old
		ui.differentWallpaper_checkBox->setCheckState(Qt::Checked);
	else
		ui.differentWallpaper_checkBox->setCheckState(Qt::Unchecked);
	
	trayObj = new QSystemTrayIcon(this);
	trayObj->setIcon(icon);
	trayObjMenu = new QMenu(this);

	exitAct=new QAction("Exit", trayObj);
	settingAct=new QAction("Settings", trayObj);
	QObject::connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));
	QObject::connect(settingAct, SIGNAL(triggered()), this, SLOT(show()));
	trayObjMenu->addAction(settingAct);
	trayObjMenu->addAction(exitAct);

	trayObj->setContextMenu(trayObjMenu);
	QObject::connect(trayObj, &QSystemTrayIcon::activated, this, &Unsplash_GUI_old::trayMenuActivated);
	trayObj->show();

	//this->loopExec(true);
	loopExecThread = std::thread(&Unsplash_GUI_old::loopExec, this, true);
}

void Unsplash_GUI_old::on_Refresh_clicked()
{
	manualRefresh = true;
	//ui.saveFolderDisp->setText("I pressed!");
}

void Unsplash_GUI_old::on_Res_changed()
{
	const QString resChoice = ui.resComboBox->currentText();
	if (!resChoice.compare("auto", Qt::CaseInsensitive))
	{
		this->setRes();
	}
	else if (!resChoice.compare("1280x720", Qt::CaseInsensitive))
	{
		//WIDTH = 1280; HEIGHT = 720;
		this->setRes(1280, 720);
	}
	else if (!resChoice.compare("1280x800", Qt::CaseInsensitive))
	{
		//WIDTH = 1280; HEIGHT = 800;
		this->setRes(1280, 800);
	}
	else if (!resChoice.compare("1440x810", Qt::CaseInsensitive))
	{
		//WIDTH = 1440; HEIGHT = 810;
		this->setRes(1440, 810);
	}
	else if (!resChoice.compare("1440x900", Qt::CaseInsensitive))
	{
		//WIDTH = 1440; HEIGHT = 900;
		this->setRes(1440, 900);
	}
	else if (!resChoice.compare("1920x1080", Qt::CaseInsensitive))
	{
		//WIDTH = 1920; HEIGHT = 1080;
		this->setRes(1920, 1080);
	}
	else if (!resChoice.compare("1920x1200", Qt::CaseInsensitive))
	{
		//WIDTH = 1920; HEIGHT = 1200;
		this->setRes(1920, 1200);
	}
	else if (!resChoice.compare("2560x1440", Qt::CaseInsensitive))
	{
		//WIDTH = 2560; HEIGHT = 1440;
		this->setRes(2560, 1440);
	}
	else if (!resChoice.compare("2560x1600", Qt::CaseInsensitive))
	{
		//WIDTH = 2560; HEIGHT = 1600;
		this->setRes(2560, 1600);
	}
	else if (!resChoice.compare("3440x1440", Qt::CaseInsensitive))
	{
		//WIDTH = 3440; HEIGHT = 1440;
		this->setRes(3440, 1440);
	}
	else if (!resChoice.compare("3840x2160", Qt::CaseInsensitive))
	{
		//WIDTH = 3840; HEIGHT = 2160;
		this->setRes(3840, 2160);
	}
	else
	{
		return;
	}
}

void Unsplash_GUI_old::on_Interval_changed()
{
	bool updateLastIdx = true;//decide whether to update the intervalComboboxLastIdx
	const QString interval = ui.intervalComboBox->currentText();
	if (!interval.compare("5 min", Qt::CaseInsensitive))
		refreshPeriod = 5 / 60.f;
	else if (!interval.compare("10 min", Qt::CaseInsensitive))
		refreshPeriod = 10 / 60.f;
	else if (!interval.compare("15 min", Qt::CaseInsensitive))
		refreshPeriod = 15 / 60.f;
	else if (!interval.compare("30 min", Qt::CaseInsensitive))
		refreshPeriod = 30 / 60.f;
	else if (!interval.compare("1 hour", Qt::CaseInsensitive))
		refreshPeriod = 1.f;
	else if (!interval.compare("2 hour", Qt::CaseInsensitive))
		refreshPeriod = 2.f;
	else if (!interval.compare("4 hour", Qt::CaseInsensitive))
		refreshPeriod = 4.f;
	else if (!interval.compare("6 hour", Qt::CaseInsensitive))
		refreshPeriod = 6.f;
	else if (!interval.compare("12 hour", Qt::CaseInsensitive))
		refreshPeriod = 12.f;
	else if (!interval.compare("1 day", Qt::CaseInsensitive))
		refreshPeriod = 24.f;
	else if (!interval.compare("Custom", Qt::CaseInsensitive))
	{
		//even if the user select OK, it will trigger another currentIdxChanged signal and the intervalComboboxLastIdx will be updated next round
		updateLastIdx = false;

		addCustomInterval dialog(this);
		/*std::fstream logFileStream;
		logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
		logFileStream << "custom interval dialog" << std::endl;
		logFileStream << dialog.exec() << std::endl;
		logFileStream << dialog.result() << std::endl;
		logFileStream.close();*/

		if (dialog.exec())//dialog.exec() seems the same as dialog.result()
		{
			QString customInterval = dialog.lineEdit->text();
			//refreshPeriod = customInterval.toFloat();
			ui.intervalComboBox->addItem(customInterval + " hour");
			ui.intervalComboBox->setCurrentText(customInterval + " hour");
		}
		else
		{
			ui.intervalComboBox->setCurrentIndex(intervalComboboxLastIdx);
			/*std::fstream logFileStream;
			logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
			logFileStream << "interval combobox display reset" << std::endl;
			logFileStream.close();	*/	
		}//end of if (dialog.exec())
	}
	else //user selected custom-set refresh interval
	{
		QStringList customIntervalSplit = interval.split(" ");
		bool floatConvert;
		float extractedFloat = customIntervalSplit[0].toFloat(&floatConvert);
		if (customIntervalSplit.length() != 2 || customIntervalSplit[1].compare("hour", Qt::CaseInsensitive) || !floatConvert)
		{
			ui.intervalComboBox->setCurrentIndex(intervalComboboxLastIdx);
			updateLastIdx = false;
			/*std::fstream logFileStream;
			logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
			logFileStream << "Unrecognized custom refresh interval selection" << interval.toStdString() << std::endl;
			logFileStream.close();*/
		}
		else
			refreshPeriod = extractedFloat;
	}
	intervalComboboxLastIdx = ui.intervalComboBox->currentIndex();
}

void Unsplash_GUI_old::on_defaultSave_clicked()
{
	this->setDefaultSaveLoc();
	ui.saveFolderDisp->setText(picFolderDir.c_str());
}

void Unsplash_GUI_old::on_changeSave_clicked()
{
	/*QFileDialog saveLocDialog(this,"Select the image save directory", picFolderDir.c_str());
	saveLocDialog.setFileMode(QFileDialog::Directory);
	saveLocDialog.setOptions(QFileDialog::ShowDirsOnly);
	if (saveLocDialog.exec())
	{
		picFolderDir=
	}*/
	QString customDir = QFileDialog::getExistingDirectory(this, tr("Select the image save directory"), 
		picFolderDir.c_str(), 
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!customDir.isEmpty())
	{
		picFolderDir = customDir.toStdString();
		picFolderDir += "/";
		ui.saveFolderDisp->setText(picFolderDir.c_str());
	}
}

void Unsplash_GUI_old::on_hide_clicked()
{
	//this->close();
	this->hide();
}

void Unsplash_GUI_old::on_About_clicked()
{
	aboutDialog aboutWindow(this);
	aboutWindow.exec();
}

void Unsplash_GUI_old::on_differentWallpaper_clicked(int state)
{
	if (state == Qt::Checked)
	{
		if (!IsWindows8OrGreater())
			ui.differentWallpaper_checkBox->setCheckState(Qt::Unchecked);
	}
}

void Unsplash_GUI_old::trayMenuActivated(QSystemTrayIcon::ActivationReason reason)
{
	/*std::fstream logFileStream;
	logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
	logFileStream << reason << std::endl;
	logFileStream.close();*/
	/*if (reason == 2) // seems when double clicked, actually get reason 3 and 2 instead of just 2; 
	{
		trayObj->showMessage("System tray", "should just reopen");
		this->show();
	}*/
	if (reason == 3)
	{
		//QMessageBox::information(0, tr("System tray"), tr("I pressed it!"));
		//trayObjMenu.setToolTipsVisible(true);
		/*QMouseEvent* e;*/
		trayObjMenu->exec(QCursor::pos()); // if just pos(), seems left click will put the context menu in a wrong position
	}
	else if (reason == 4)
	{
		trayObj->showMessage("System tray", "What's up?");
	}
}

//void Unsplash_GUI_old::closeEvent(QCloseEvent* e)
//{
//	e->ignore();
//	this->hide();
//}

Unsplash_GUI_old::~Unsplash_GUI_old()
{
	loopExecThread.detach();
	loopExecThread.~thread();
	delete trayObj, trayObjMenu, exitAct, settingAct;
	trayObj = NULL;
	trayObjMenu = NULL;
	exitAct = NULL;
	settingAct = NULL;
}