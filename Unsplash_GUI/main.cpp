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
		Unsplash_GUI w;
		w.hide();
		//w.loopExec(true);
		return a.exec();
	}
	else
	{
		QApplication a(argc, argv);
		Unsplash_GUI_old w;
		w.hide();
		//w.loopExec(true);
		return a.exec();
	}
}