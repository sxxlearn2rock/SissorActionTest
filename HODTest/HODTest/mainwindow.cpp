#include "mainwindow.h"
#include <windows.h>
#include <time.h>
#include <iostream>

#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <qdebug.h>

using namespace cv;


MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),mReady2PalyVideo(false), mStopPlayVideo(false)
{
	ui.setupUi(this);
	mQTimer = new QTimer();

	connect(mQTimer, SIGNAL(timeout()), this, SLOT(displayInputMat()));			
}

MainWindow::~MainWindow()
{

}


void MainWindow::on_acOpenVideo_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("��ѡ����Ƶ�ļ�"), ".", tr("video file(*.*)"));
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

	//��ȡ����ʾ��Ƶ�ĵ�һ֡ͼ�񣬱�ʾ��Ƶ�Ѿ��ɹ���ȡ
	mVideoCapture >> mInputMat;
	displayMat(mInputMat);

	mReady2PalyVideo = true;

}


void MainWindow::on_acExit_triggered()
{
	if (!(QMessageBox::information(this,tr("�˳�"),tr("���Ҫ�˳�������"),tr("��"),tr("��"))))
	{
		this->close();
	}
}

void MainWindow::displayMat(cv::Mat& image)
{
	Mat rgb;
	if(image.channels()==3)
	{
		//cvt Mat BGR 2 QImage RGB
		cvtColor(image,rgb,CV_BGR2RGB);
		mInputQImage =QImage((const unsigned char*)(rgb.data),
			rgb.cols,rgb.rows,
			rgb.cols*rgb.channels(),
			QImage::Format_RGB888);
	}
	else
	{
		mInputQImage =QImage((const unsigned char*)(image.data),
			image.cols,image.rows,
			image.cols*image.channels(),
			QImage::Format_RGB888);
	}
//	ui.labelInputFrame->clear();
	ui.labelInputFrame->setPixmap(QPixmap::fromImage(mInputQImage));
	ui.labelInputFrame->resize(QSize(ui.frameInputBox->frameRect().width(),ui.frameInputBox->frameRect().height()));

}

void MainWindow::on_btnStartDetect_clicked()
{
	displayInputVideo();
}


void MainWindow::displayInputVideo()
{
	if (!mReady2PalyVideo)
	{
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::OPEN_FILE_FAILURE);
		return;
	}
	
	double rate = mVideoCapture.get(CV_CAP_PROP_FPS);
	int delay = 1000/rate;
	
	mQTimer->start(delay);

}

void MainWindow::displayInputMat()
{
	if (mVideoCapture.read(mInputMat))
	{	
		displayMat(mInputMat);

	}else{
		mQTimer->stop();
		ui.labelInputFrame->setText(tr("   ��Ƶ���Ž�����"));
		mVideoCapture.release();
	}
	

}



