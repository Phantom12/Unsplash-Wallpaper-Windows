#include "unsplash_gui.h"
#include <qtwidgets/qapplication>
#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Unsplash_GUI w;
	w.show();
	//w.loopExec(true);
	return a.exec();
}