#ifndef MODULETEST_H
#define MODULETEST_H

#include <QtGui/QMainWindow>
#include <QMessageBox>  
#include <QComboBox>
#include "ui_moduletest.h"

class ModuleTest : public QMainWindow
{
	Q_OBJECT

public:
	ModuleTest(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ModuleTest();

private:
	Ui::ModuleTestClass ui;
	QComboBox *cbo_sex;  

private slots:  
		void on_sel_sex()  
		{  
			QString str;  
			str = "You select ";  
			QMessageBox::information(this, tr("Info"), str);  
		}  

		void on_click_sel()  
		{  
			QString str;  
			str = ("You select %1" + cbo_sex->currentText()).arg(cbo_sex->currentIndex());  
			QMessageBox::information(this, tr("Info"), str);  
		}  

};

#endif // MODULETEST_H
