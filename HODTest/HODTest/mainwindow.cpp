#include "mainwindow.h"

#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <qdebug.h>

using namespace cv;


MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}


void MainWindow::on_acOpenVideo_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("请选择视频文件"), ".", tr("video file(*.*)"));
	if( fileName == NULL)  
	{  
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::NULL_PATH);
		return;
	} 

	mVideoCapture.open(fileName.toAscii().data());
	if( !mVideoCapture.isOpened() )  
	{  
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::OPEN_FILE_FAILURE);
		return;
	} 

	mVideoCapture >> mInputMat;
	displayMat(mInputMat);
}


void MainWindow::on_acExit_triggered()
{
	if (!(QMessageBox::information(this,tr("退出"),tr("真的要退出程序吗？"),tr("是"),tr("否"))))
	{
		this->close();
	}
}

void MainWindow::displayMat(cv::Mat& image)
{
	Mat rgb;
	QImage qImage;
	if(image.channels()==3)
	{
		//cvt Mat BGR 2 QImage RGB
		cvtColor(image,rgb,CV_BGR2RGB);
		qImage =QImage((const unsigned char*)(rgb.data),
			rgb.cols,rgb.rows,
			rgb.cols*rgb.channels(),
			QImage::Format_RGB888);
	}
	else
	{
		qImage =QImage((const unsigned char*)(image.data),
			image.cols,image.rows,
			image.cols*image.channels(),
			QImage::Format_RGB888);
	}
	ui.labelInputFrame->clear();
	ui.labelInputFrame->setPixmap(QPixmap::fromImage(qImage));
	ui.labelInputFrame->resize(QSize(ui.frameInputBox->frameRect().width(),ui.frameInputBox->frameRect().height()));

}


