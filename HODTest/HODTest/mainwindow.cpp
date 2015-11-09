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
	//���ù�����
	ui.mainToolBar->addAction(ui.acReadVideo);	
	ui.mainToolBar->addAction(ui.acStartDetect);
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(ui.acReadPic);
	ui.mainToolBar->addAction(ui.acStartDetectPic);
	//����״̬��
	uStatusLabel = new QLabel();
	uStatusLabel->setMinimumSize(uStatusLabel->sizeHint());
	uStatusLabel->setAlignment(Qt::AlignHCenter);
	this->statusBar()->addWidget(uStatusLabel);
	//���ø���������״̬����ʾ��Ϣ
	ui.acReadVideo->setStatusTip(tr("��һ����Ƶ�ļ�"));
	ui.acStartDetect->setStatusTip(tr("��ʼ���е��߼��"));
	ui.acReadPic->setStatusTip(tr("��һ��ͼƬ�ļ�"));
	ui.acStartDetectPic->setStatusTip(tr("��ʼ��ͼƬ���м��"));
	ui.acExit->setStatusTip(tr("�˳�����"));

	mQTimer = new QTimer();

	mDenoiseProcessor = DenoiseProcessor::getInstance();
	mDenoiseProcessor->setDenoiseStrategy(DefaultDenosieStrategy::getInstance());

	mSegmentProcessor = SegmentProcessor::getInstance();
	mSegmentProcessor->setSegmentStrategy(DefaultSegmentStrategy::getInstance());

	//��ʽ�źŲ�����
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
	QString fileName = QFileDialog::getOpenFileName(this,tr("��ѡ����Ƶ�ļ�"), ".", tr("video file(*.*)"));
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

	//��ȡ����ʾ��Ƶ�ĵ�һ֡ͼ�񣬱�ʾ��Ƶ�Ѿ��ɹ���ȡ
	mVideoCapture >> mInputMat;
	displayMat(mInputMat, ui.labelInputFrame, ui.frameInputBox);

	mIsVideoMode = true;
	mVideoIsOver =false;
	mReady2Process = true;

}

void MainWindow::on_acReadPic_triggered()
{
	
	QString fileName = QFileDialog::getOpenFileName(this,tr("��ѡ��ͼƬ�ļ�"), ".", tr("iamge file(*.*)"));
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
	//Mat��ȡ����bgr��ʽ��Ҫ����ת��rgb��ʽ��QImage
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
			QImage::Format_Indexed8);		//ע��˴���ָʾΪ8λ�Ҷ�ͼ
	}

	//���������frameInputBox������ʾͼƬ
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
	//��֮ǰ֡û�д����꣬��������֡
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
			//ֹͣ��ʱ��
			mQTimer->stop();
			mReady2Process = false;
			//�����������
			clearAllFrame();
			//�ͷ���Դ
			releaseResource();
			QMessageBox::information(this, tr("֪ͨ"), tr("��Ƶ���Ž�����"));
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

//ȥ���㷨���������ʱ������ȥ�����
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

//�ָ��㷨���������ʱ�����ķָ�߿�
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
	//�ͷ���Ƶ��Դ
	if (mVideoCapture.isOpened())
	{
		mVideoCapture.release();
	}
	//�ͷŸ���mat
	mDenoiseMat.empty();
	mSegmentMat.empty();
	mMorphMat.empty();
	mRecogniseMat.empty();
	mOutputMat.empty();
}

void MainWindow::on_acExit_triggered()
{
	if (!(QMessageBox::information(this,tr("�˳�"),tr("���Ҫ�˳�������"),tr("��"),tr("��"))))
	{
		this->close();
	}
}











