#ifndef CONFIGDLG_H
#define CONFIGDLG_H

#include <QDialog>
#include "ui_configdlg.h"

class ConfigDlg : public QDialog
{
	Q_OBJECT

public:
	ConfigDlg(QWidget *parent = 0);
	~ConfigDlg();

private:
	Ui::ConfigDlg ui;
};

#endif // CONFIGDLG_H
