#include "unsplash_gui.h"
#include "unsplash_gui_old.h"
#include <qtwidgets/qapplication>
#include <iostream>
#include <thread>
#include <VersionHelpers.h>

int main(int argc, char *argv[])
{
	if (IsWindows8OrGreater())
	{
		QApplication a(argc, argv);
		//apply QDarkStyleSheet (https://github.com/ColinDuquesnoy/QDarkStyleSheet)
		QFile styleFile(":/qdarkstyle/style.qss");
		styleFile.open(QFile::ReadOnly);
		QString style(styleFile.readAll());
		a.setStyleSheet(style);
		Unsplash_GUI w;
		w.hide();
		//w.loopExec(true);
		return a.exec();
	}
	else
	{
		QApplication a(argc, argv);
		QFile styleFile(":/qdarkstyle/style.qss");
		styleFile.open(QFile::ReadOnly);
		QString style(styleFile.readAll());
		a.setStyleSheet(style);
		Unsplash_GUI_old w;
		w.hide();
		//w.loopExec(true);
		return a.exec();
	}
}