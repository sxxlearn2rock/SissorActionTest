#include "moduletest.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ModuleTest w;
	w.show();
	return a.exec();
}
