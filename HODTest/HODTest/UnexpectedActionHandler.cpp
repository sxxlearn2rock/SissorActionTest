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
	msgBox.setWindowTitle(QObject::tr("���棡"));
	msgBox.setWindowIcon(QIcon(":/Resources/warning.png"));
	msgBox.setIcon(QMessageBox::Icon::Critical);

	switch (c)
	{
	case NULL_PATH:		
		msgBox.setText(QObject::tr("û��ѡ���κ��ļ���"));  
		msgBox.exec();
		break;
	case OPEN_FILE_FAILURE:		
		msgBox.setText(QObject::tr("����Ƶ�ļ�ʧ�ܣ�"));  
		msgBox.exec();
		break;
	default: break;
	}
}
