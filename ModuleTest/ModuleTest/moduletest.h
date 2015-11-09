#ifndef MODULETEST_H
#define MODULETEST_H

#include <QtGui/QMainWindow>
#include <QMessageBox>  
#include <QComboBox>
#include "ui_moduletest.h"
#include "configdlg.h"

class ModuleTest : public QMainWindow
{
	Q_OBJECT

public:
	ModuleTest(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ModuleTest();

	void setArg0( int arg ) { mArg0 = arg; }

private:
	Ui::ModuleTestClass ui;
	ConfigDlg* mConfigDlg;

	int mArg0;


private slots:  
	void on_btnShowDlg_clicked();
};

#endif // MODULETEST_H
