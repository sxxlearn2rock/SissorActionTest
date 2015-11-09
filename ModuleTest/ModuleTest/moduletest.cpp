#include "moduletest.h"
#include <QPushButton>  
#include <QLineEdit>  
#include <QLayout>  
#include <QLabel>  
#include <QComboBox>  
#include <QMessageBox>  
#include <QDialog>  

ModuleTest::ModuleTest(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), mArg0(0)
{
	ui.setupUi(this);

	mConfigDlg = new ConfigDlg(this);
}

ModuleTest::~ModuleTest()
{

}

void ModuleTest::on_btnShowDlg_clicked()
{
	mConfigDlg->exec();
}
