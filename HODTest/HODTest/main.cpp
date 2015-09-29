#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowTitle(QObject::tr("ºÙµ∂––∂Ø≤‚ ‘≥Ã–Ú"));
	w.setWindowIcon(QIcon(":/Resources/sissor.png"));
	w.show();
	return a.exec();
}
