#include "mainwindow.h"
#include "./Processors/strategies.h"
#include <windows.h>
#include <time.h>
#include <iostream>

#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <qdebug.h>

using namespace cv;


MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),mReady2Process(false), mStopPlayVideo(false), mIsProcessing(false), mVideoIsOver(false)
	,mIsVideoMode(true)
{
	ui.setupUi(this);
	//配置工具栏
	ui.mainToolBar->addAction(ui.acReadVideo);	
	ui.mainToolBar->addAction(ui.acStartDetect);
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(ui.acReadPic);
	ui.mainToolBar->addAction(ui.acStartDetectPic);
	//配置状态栏
	uStatusLabel = new QLabel();
	uStatusLabel->setMinimumSize(uStatusLabel->sizeHint());
	uStatusLabel->setAlignment(Qt::AlignHCenter);
	this->statusBar()->addWidget(uStatusLabel);
	//配置各个部件的状态栏提示信息
	ui.acReadVideo->setStatusTip(tr("打开一个视频文件"));
	ui.acStartDetect->setStatusTip(tr("开始进行刀具检测"));
	ui.acReadPic->setStatusTip(tr("打开一个图片文件"));
	ui.acStartDetectPic->setStatusTip(tr("开始对图片进行检测"));
	ui.acExit->setStatusTip(tr("退出程序"));

	mQTimer = new QTimer();

	mDenoiseProcessor = DenoiseProcessor::getInstance();
	mDenoiseProcessor->setDenoiseStrategy(DefaultDenosieStrategy::getInstance());

	mSegmentProcessor = SegmentProcessor::getInstance();
	mSegmentProcessor->setSegmentStrategy(DefaultSegmentStrategy::getInstance());

	//显式信号槽链接
	connect(mQTimer, SIGNAL(timeout()), this, SLOT(totalProcess()));
}

MainWindow::~MainWindow()
{
	releaseResource();
	delete mDenoiseProcessor;
	delete mSegmentProcessor;
}


void MainWindow::on_acReadVideo_triggered()
{	
	QString fileName = QFileDialog::getOpenFileName(this,tr("请选择视频文件"), ".", tr("video file(*.*)"));
	if( fileName == NULL)  
	{  
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::NULL_PATH);
		return;
	} 

	mVideoCapture.open(fileName.toLocal8Bit().data());
	if( !mVideoCapture.isOpened() )  
	{  
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::OPEN_FILE_FAILURE);
		return;
	} 

	//读取并显示视频的第一帧图像，表示视频已经成功读取
	mVideoCapture >> mInputMat;
	displayMat(mInputMat, ui.labelInputFrame, ui.frameInputBox);

	mIsVideoMode = true;
	mVideoIsOver =false;
	mReady2Process = true;

}

void MainWindow::on_acReadPic_triggered()
{
	
	QString fileName = QFileDialog::getOpenFileName(this,tr("请选择图片文件"), ".", tr("iamge file(*.*)"));
	if( fileName == NULL)  
	{  
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::NULL_PATH);
		return;
	} 

	mInputMat= imread(fileName.toLocal8Bit().data());
	if( !mInputMat.data )  
	{  
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::OPEN_FILE_FAILURE);
		return;
	}

	clearAllFrame();
	displayMat(mInputMat, ui.labelInputFrame, ui.frameInputBox);

	mIsVideoMode = false;
	mReady2Process = true;
}



void MainWindow::on_acStartDetect_triggered()
{
	if (!mReady2Process)
	{
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::OPEN_FILE_FAILURE);
		return;
	}

	if (mIsVideoMode)
	{
		double videoRate = mVideoCapture.get(CV_CAP_PROP_FPS);
		int delayBetween2Frames = 1000/videoRate;

		mQTimer->start(delayBetween2Frames);
	}
}


void MainWindow::on_acStartDetectPic_triggered()
{
	if (!mReady2Process)
	{
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::OPEN_FILE_FAILURE);
		return;
	}

	if (!mIsVideoMode)
	{
		displayDenoisedMat();
		displaySegedMat();
		displayOutputMat();
	}
}


void MainWindow::displayMat(cv::Mat& image, QLabel* label2show, QFrame* frame2show)
{
	//Mat采取的是bgr格式，要将其转化rgb格式的QImage
	Mat rgb;
	QImage qImage;
	if(image.channels()==3)
	{
		//cvt Mat BGR 2 QImage RGB
		cvtColor(image,rgb,CV_BGR2RGB);
		qImage =QImage((const unsigned char*)(rgb.data),
			rgb.cols,
			rgb.rows,
			rgb.cols*rgb.channels(),
			QImage::Format_RGB888);
	}
	else
	{
			qImage =QImage((const unsigned char*)(image.data),
			image.cols,
			image.rows,
			image.cols*image.channels(),
			QImage::Format_Indexed8);		//注意此处需指示为8位灰度图
	}

	//在主界面的frameInputBox里面显示图片
	label2show->setPixmap(QPixmap::fromImage(qImage));
	label2show->resize(QSize(frame2show->frameRect().width(),frame2show->frameRect().height()));

}


void MainWindow::displayInputMat()
{
	if (mVideoCapture.read(mInputMat))
	{	
		displayMat(mInputMat, ui.labelInputFrame, ui.frameInputBox);

	}else{
		mVideoIsOver = true;
	}
}

void MainWindow::displayDenoisedMat()
{
	mDenoiseProcessor->process(mInputMat, mDenoiseMat);
	displayMat(mDenoiseMat, ui.labelDenoiseFrame, ui.frameDenoiseBox);
}

void MainWindow::displaySegedMat()
{
	mSegmentProcessor->process(mDenoiseMat, mSegmentMat, mMorphMat, coordinates, rotatedRects);
	displayMat(mSegmentMat, ui.labelSegmentFrame, ui.frameSegmentBox);
	displayMat(mMorphMat, ui.labelMorphFrame, ui.frameMorphBox);
}

void MainWindow::displayOutputMat()
{
//	mOutputMat = mInputMat;
	displayMat(mOutputMat, ui.labelOutputFrame, ui.frameOutputBox);
}

void MainWindow::totalProcess()
{
	//若之前帧没有处理完，就跳过该帧
	if ( (!mIsProcessing) )
	{	
		mIsProcessing = true;
		displayInputMat();
		if ( !mVideoIsOver )
		{	
			displayDenoisedMat();
			displaySegedMat();
			displayOutputMat();	
		}else
		{
			//停止定时器
			mQTimer->stop();
			mReady2Process = false;
			//清理各个窗口
			clearAllFrame();
			//释放资源
			releaseResource();
			QMessageBox::information(this, tr("通知"), tr("视频播放结束！"));
		}
		mIsProcessing = false;
	}

}

void MainWindow::on_comboDenoise_currentIndexChanged()
{
	setDenoiseStrategy(ui.comboDenoise->currentIndex());
}

void MainWindow::on_comboSegment_currentIndexChanged()
{
	setSegmentStrategy(ui.comboSegment->currentIndex());
}

//去噪算法下拉框更改时，更改去噪策略
void MainWindow::setDenoiseStrategy(int index)
{
	switch (index)
	{
	case 0:
		mDenoiseProcessor->setDenoiseStrategy(DefaultDenosieStrategy::getInstance());		break;
	case 1:
		mDenoiseProcessor->setDenoiseStrategy(LateralInhibition::getInstance());		break;
	case 2:
		mDenoiseProcessor->setDenoiseStrategy(MaxMedianFilter::getInstance());		break;
	case 3:
		mDenoiseProcessor->setDenoiseStrategy(LocalMeanContrast::getInstance());		break;	
	default:
		mDenoiseProcessor->setDenoiseStrategy(DefaultDenosieStrategy::getInstance());		break;
	}
}

//分割算法下拉框更改时，更改分割策咯
void MainWindow::setSegmentStrategy(int index)
{
	switch (index)
	{
	case 0:
		mSegmentProcessor->setSegmentStrategy(DefaultSegmentStrategy::getInstance());		break;
	case 1:
		mSegmentProcessor->setSegmentStrategy(OtsuSegment::getInstance());		break;
	case 2:
		mSegmentProcessor->setSegmentStrategy(KswSegment::getInstance());		break;
	case 3:
		mSegmentProcessor->setSegmentStrategy(Ksw2dSegment::getInstance());		break;
	default:
		mSegmentProcessor->setSegmentStrategy(DefaultSegmentStrategy::getInstance());
		break;
	}
}

void MainWindow::clearAllFrame()
{
	ui.labelInputFrame->clear();
	ui.labelDenoiseFrame->clear();
	ui.labelSegmentFrame->clear();
	ui.labelMorphFrame->clear();
	ui.labelOutputFrame->clear();
	ui.labelRecogFrame->clear();
}

void MainWindow::releaseResource()
{
	//释放视频资源
	if (mVideoCapture.isOpened())
	{
		mVideoCapture.release();
	}
	//释放各个mat
	mDenoiseMat.empty();
	mSegmentMat.empty();
	mMorphMat.empty();
	mRecogniseMat.empty();
	mOutputMat.empty();
}

void MainWindow::on_acExit_triggered()
{
	if (!(QMessageBox::information(this,tr("退出"),tr("真的要退出程序吗？"),tr("是"),tr("否"))))
	{
		this->close();
	}
}











