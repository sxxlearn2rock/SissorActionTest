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

	//显式信号槽链接
	connect(mQTimer, SIGNAL(timeout()), this, SLOT(displayInputMat()));
	connect(mQTimer, SIGNAL(timeout()), this, SLOT(displayOutputMat()));		
}

MainWindow::~MainWindow()
{

}


void MainWindow::on_acReadVideo_triggered()
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

	//读取并显示视频的第一帧图像，表示视频已经成功读取
	mVideoCapture >> mInputMat;
	displayMat(mInputMat, ui.labelInputFrame, ui.frameInputBox);

	mReady2PalyVideo = true;

}


void MainWindow::on_acExit_triggered()
{
	if (!(QMessageBox::information(this,tr("退出"),tr("真的要退出程序吗？"),tr("是"),tr("否"))))
	{
		this->close();
	}
}

void MainWindow::displayMat(cv::Mat& image, QLabel* labelwshow, QFrame* frame2show)
{
	//Mat采取的是bgr格式，要将其转化rgb格式的QImage
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

	//在主界面的frameInputBox里面显示图片
	labelwshow->setPixmap(QPixmap::fromImage(mInputQImage));
	labelwshow->resize(QSize(frame2show->frameRect().width(),frame2show->frameRect().height()));

}

void MainWindow::on_btnStartDetect_clicked()
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
		displayMat(mInputMat, ui.labelInputFrame, ui.frameInputBox);

	}else{
		//停止定时器
		mQTimer->stop();
		ui.labelInputFrame->setText(tr("                    视频播放结束！"));
		//释放视频资源
		mVideoCapture.release();
	}
	

}

void MainWindow::displayOutputMat()
{

	rectangle(mInputMat, Rect(20,20,200,200), Scalar(32, 102, 255), 2);
	displayMat(mInputMat, ui.labelOutputFrame, ui.frameOutputBox);
}



