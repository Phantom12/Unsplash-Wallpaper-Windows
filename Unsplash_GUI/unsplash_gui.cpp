#include "unsplash_gui.h"
#include "qfiledialog.h"
#include <thread>
#include "QtConcurrent\qtconcurrentrun.h"
#include "addcustominterval.h"
#include <fstream>
#include "aboutdialog.h"
#include "qmessagebox.h"
#include <ShlObj.h>
#include <Shlwapi.h>

//Unless otherwise specified, the constructors of a derived class calls the default constructor of its base classes
Unsplash_GUI::Unsplash_GUI(QWidget *parent)
	: QMainWindow(parent)
{

	QString localSettingFile = getenv("LOCALAPPDATA");
	localSettingFile += "\\Unsplash_GUI\\config.ini";
	settings = new QSettings(localSettingFile, QSettings::IniFormat);
	QIcon icon(":/image/minecart_cropped.ico");
	this->setWindowIcon(icon);

	ui.setupUi(this);
	ui.mainToolBar->hide();

	//check if different per monitor option is specified in the config.ini
	QVariant perMonitor= settings->value("Different_Per_Monitor");
	if (!perMonitor.isNull())
		differentWallpaperPerMonitor = perMonitor.toBool();
	else
	{
		settings->setValue("Different_Per_Monitor", differentWallpaperPerMonitor);
		/*std::fstream logFileStream;
		logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
		logFileStream << "null" << std::endl;
		logFileStream.close();*/
	}

	if (differentWallpaperPerMonitor)
		ui.differentWallpaper_checkBox->setCheckState(Qt::Checked);
	else
		ui.differentWallpaper_checkBox->setCheckState(Qt::Unchecked);

	//if (IsWindows8OrGreater()) //consistent with the definition of differentWallpaperPerMonitor in Unsplash_Wei
	//	ui.differentWallpaper_checkBox->setCheckState(Qt::Checked);
	//else
	//	ui.differentWallpaper_checkBox->setCheckState(Qt::Unchecked);

	// check if the preferred refresh interval exists
	QString interval = settings->value("Refresh_Interval").toString();
	/*std::fstream logFileStream;
	logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
	logFileStream << interval.toStdString() << std::endl;
	logFileStream << interval.compare("2 hour", Qt::CaseInsensitive) << std::endl;
	logFileStream.close();*/
	if (interval.isEmpty())
	{
		settings->setValue("Refresh_Interval", "1 hour");
		ui.intervalComboBox->setCurrentText("1 hour");
	}
	else
	{
		if (!interval.compare("5 min", Qt::CaseInsensitive))
		{
			//refreshPeriod = 5 / 60.f;
			ui.intervalComboBox->setCurrentText("5 min"); // automatically triggered on_Interval_changed()
		}
		else if (!interval.compare("10 min", Qt::CaseInsensitive))
		{
			//refreshPeriod = 10 / 60.f;
			ui.intervalComboBox->setCurrentText("10 min");
		}
		else if (!interval.compare("15 min", Qt::CaseInsensitive))
		{
			//refreshPeriod = 15 / 60.f;
			ui.intervalComboBox->setCurrentText("15 min");
		}
		else if (!interval.compare("30 min", Qt::CaseInsensitive))
		{
			//refreshPeriod = 30 / 60.f;
			ui.intervalComboBox->setCurrentText("30 min");
		}
		else if (!interval.compare("1 hour", Qt::CaseInsensitive))
		{
			//refreshPeriod = 1.f;
			ui.intervalComboBox->setCurrentText("1 hour");
		}
		else if (!interval.compare("2 hour", Qt::CaseInsensitive))
		{
			//refreshPeriod = 2.f;
			ui.intervalComboBox->setCurrentText("2 hour");
		}
		else if (!interval.compare("4 hour", Qt::CaseInsensitive))
		{
			//refreshPeriod = 4.f; 
			ui.intervalComboBox->setCurrentText("4 hour");
		}
		else if (!interval.compare("6 hour", Qt::CaseInsensitive))
		{
			//refreshPeriod = 6.f;
			ui.intervalComboBox->setCurrentText("6 hour");
		}
		else if (!interval.compare("12 hour", Qt::CaseInsensitive))
		{
			//refreshPeriod = 12.f; 
			ui.intervalComboBox->setCurrentText("12 hour");
		}
		else if (!interval.compare("1 day", Qt::CaseInsensitive))
		{
			//refreshPeriod = 24.f;
			ui.intervalComboBox->setCurrentText("1 day");
		}
		else if (!interval.right(4).compare("hour", Qt::CaseInsensitive))
		{
			//refreshPeriod = interval.left(interval.length() - 4).toFloat();
			ui.intervalComboBox->addItem(interval);
			ui.intervalComboBox->setCurrentText(interval);
			/*std::fstream logFileStream;
			logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
			logFileStream << refreshPeriod << std::endl;
			logFileStream.close();*/
		}
		else //unrecognized setting
		{
			settings->setValue("Refresh_Interval", "1 hour");
			ui.intervalComboBox->setCurrentText("1 hour");
		}
	}
	intervalComboboxLastIdx = ui.intervalComboBox->currentIndex();

	// check if the wallpaper save location exists in the config.ini
	QString saveLoc = settings->value("Save_Location").toString();
	if (saveLoc.isEmpty())
	{
		/*std::fstream logFileStream;
		logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
		std::string tempStr = saveLoc.toStdString();
		logFileStream << tempStr.c_str() << std::endl;
		logFileStream.close();*/
		settings->setValue("Save_Location", QString(picFolderDir.c_str()));
	}
	else
		picFolderDir = saveLoc.toStdString();
	ui.saveFolderDisp->setText(picFolderDir.c_str());
	//system(("mkdir " + picFolderDir).c_str()); // mkdir only works with backslash

	// check if the preferred resolution settings exist
	int wallpaperW = settings->value("Width").toInt();
	int wallpaperH = settings->value("Height").toInt();

	if (wallpaperH*wallpaperW)
	{
		//setRes(wallpaperW, wallpaperH);
		std::string lclResComboBoxText = std::to_string(wallpaperW) + "x" + std::to_string(wallpaperH);
		ui.resComboBox->setCurrentText(lclResComboBoxText.c_str());
	}
	else
	{
		ui.resComboBox->setCurrentText("Auto");
		settings->setValue("Width", 0);
		settings->setValue("Height", 0);
	}
	
	// check if the auto start link exists
	PWSTR autoStartPath; //wchar string
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	hr = SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &autoStartPath); //retrive the start up folder direction of the current user
	if (SUCCEEDED(hr))
	{
		WCHAR currentFile[256];
		GetModuleFileName(NULL, currentFile, 256);
		std::wstring ShortcutFile(autoStartPath);
		ShortcutFile += L"\\";
		ShortcutFile += PathFindFileName(currentFile);
		ShortcutFile = ShortcutFile.substr(0, ShortcutFile.length() - 3); // remove "exe" from the shortcut name
		ShortcutFile += L"lnk";
		std::string ShortcutFileA(ShortcutFile.begin(), ShortcutFile.end());
		// http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
		if (std::FILE* shortcut = fopen(ShortcutFileA.c_str(), "r"))
		{
			fclose(shortcut);
			ui.autoStartCheckBox->setCheckState(Qt::Checked); 
			// will trigger on_autoStart_clicked(), overwrite the shortcut, and therefore works even if user moves the .exe file location
		}
		else
			ui.autoStartCheckBox->setCheckState(Qt::Unchecked);
	}
	else
		ui.autoStartCheckBox->setCheckState(Qt::Unchecked);

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
	QObject::connect(trayObj, &QSystemTrayIcon::activated, this, &Unsplash_GUI::trayMenuActivated);
	trayObj->show();

	//this->loopExec(true);
	loopExecThread = std::thread(&Unsplash_GUI::loopExec, this, true);
}

void Unsplash_GUI::on_Refresh_clicked()
{
	manualRefresh = true;
	//ui.saveFolderDisp->setText("I pressed!");
}

void Unsplash_GUI::on_Res_changed()
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

	// update .ini setting file
	if (!resChoice.compare("auto", Qt::CaseInsensitive))
	{
		settings->setValue("Width", 0);
		settings->setValue("Height", 0);
	}
	else
	{
		settings->setValue("Width", WIDTH);
		settings->setValue("Height", HEIGHT);
	}
}

void Unsplash_GUI::on_Interval_changed()
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
	settings->setValue("Refresh_Interval", ui.intervalComboBox->currentText());
}

void Unsplash_GUI::on_defaultSave_clicked()
{
	this->setDefaultSaveLoc();
	ui.saveFolderDisp->setText(picFolderDir.c_str());
	settings->setValue("Save_Location", QString(picFolderDir.c_str()));
}

void Unsplash_GUI::on_changeSave_clicked()
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
	settings->setValue("Save_Location", QString(picFolderDir.c_str()));
}

void Unsplash_GUI::on_hide_clicked()
{
	//this->close();
	this->hide();
}

void Unsplash_GUI::on_About_clicked()
{
	aboutDialog aboutWindow(this);
	aboutWindow.exec();
}

void Unsplash_GUI::on_differentWallpaper_clicked(int state)
{
	if (state == Qt::Checked)
	{
		if (!IsWindows8OrGreater())
		{
			ui.differentWallpaper_checkBox->setCheckState(Qt::Unchecked);
			differentWallpaperPerMonitor = false;
		}
		else
			differentWallpaperPerMonitor = true;
	}
	else
	{
		differentWallpaperPerMonitor = false;
		/*std::fstream logFileStream;
		logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
		logFileStream << "come on! I called differentWallpaperPerMonitor false" << std::endl;
		logFileStream.close();*/
	}
	settings->setValue("Different_Per_Monitor", differentWallpaperPerMonitor);
}

//http://stackoverflow.com/questions/15579932/c-how-do-we-make-our-application-start-on-computer-startup-and-of-course-aft
void Unsplash_GUI::on_autoStart_clicked(int state)
{
	if (state == Qt::Checked)
	{
		PWSTR autoStartPath; //wchar string
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

		hr = SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &autoStartPath); //retrive the start up folder direction of the current user

		if (SUCCEEDED(hr)) // use the shell link to add the program to the autoStart folder
		{
			IShellLink* pShellLink = NULL;
			hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pShellLink);
			if (SUCCEEDED(hr))
			{
				IPersistFile* ppf;
				WCHAR currentFile[256];
				GetModuleFileName(NULL, currentFile, 256);
				//pShellLink->SetPath(L"C:\\Users\\wegu\\Desktop\\Unsplash_GUI\\x64\\Release\\Unsplash_GUI.exe");
				pShellLink->SetPath(currentFile);
				pShellLink->SetDescription(L"Shortcut to Unsplash Wallpaper");
				//logFileStream << SUCCEEDED(hr) << std::endl;

				hr = pShellLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
				if (SUCCEEDED(hr))
				{
					std::wstring ShortcutFile(autoStartPath);
					ShortcutFile += L"\\";
					ShortcutFile += PathFindFileName(currentFile);
					ShortcutFile = ShortcutFile.substr(0, ShortcutFile.length() - 3); // remove "exe" from the shortcut name
					ShortcutFile += L"lnk";
					//hr = ppf->Save(L"C:\\Work\\test.lnk", TRUE);
					hr = ppf->Save(ShortcutFile.c_str(), TRUE);
					ppf->Release();
					if (FAILED(hr))
						ui.autoStartCheckBox->setCheckState(Qt::Unchecked);
				}
				else
					ui.autoStartCheckBox->setCheckState(Qt::Unchecked);
			}
			else
				ui.autoStartCheckBox->setCheckState(Qt::Unchecked);

			pShellLink->Release();
		}
		else
			ui.autoStartCheckBox->setCheckState(Qt::Unchecked);

	} // if checked
	else // delete the shortcut from the startup folder
	{
		PWSTR autoStartPath; //wchar string
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		hr = SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &autoStartPath); //retrive the start up folder direction of the current user
		if (SUCCEEDED(hr))
		{
			WCHAR currentFile[256];
			GetModuleFileName(NULL, currentFile, 256);
			std::wstring ShortcutFile(autoStartPath);
			ShortcutFile += L"\\";
			ShortcutFile += PathFindFileName(currentFile);
			ShortcutFile = ShortcutFile.substr(0, ShortcutFile.length() - 3); // remove "exe" from the shortcut name
			ShortcutFile += L"lnk";
			std::string ShortcutFileA(ShortcutFile.begin(), ShortcutFile.end());
			if (remove(ShortcutFileA.c_str()))
				ui.autoStartCheckBox->setCheckState(Qt::Checked);
		}
		else
			ui.autoStartCheckBox->setCheckState(Qt::Checked);
	}
}

void Unsplash_GUI::trayMenuActivated(QSystemTrayIcon::ActivationReason reason)
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

//void Unsplash_GUI::closeEvent(QCloseEvent* e)
//{
//	e->ignore();
//	this->hide();
//}

Unsplash_GUI::~Unsplash_GUI()
{
	loopExecThread.detach();
	loopExecThread.~thread();
	delete trayObj, trayObjMenu, exitAct, settingAct;
	trayObj = NULL;
	trayObjMenu = NULL;
	exitAct = NULL;
	settingAct = NULL;
	settings = NULL;
}