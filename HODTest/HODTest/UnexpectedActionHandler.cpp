#include "UnexpectedActionHandler.h"
#include <QtGui/QMessageBox>
#include <QtGui/QIcon>

UnexpectedActionHandler::UnexpectedActionHandler(void)
{
}


UnexpectedActionHandler::~UnexpectedActionHandler(void)
{
}

void UnexpectedActionHandler::handle(Condition c)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(QObject::tr("警告！"));
	msgBox.setWindowIcon(QIcon(":/Resources/warning.png"));
	msgBox.setIcon(QMessageBox::Icon::Critical);

	switch (c)
	{
	case NULL_PATH:		
		msgBox.setText(QObject::tr("没有选择任何文件！"));  
		msgBox.exec();
		break;
	case OPEN_FILE_FAILURE:		
		msgBox.setText(QObject::tr("打开视频文件失败！"));  
		msgBox.exec();
		break;
	default: break;
	}
}
