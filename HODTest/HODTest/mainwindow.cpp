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
	: QMainWindow(parent, flags),mReady2PalyVideo(false), mStopPlayVideo(false), mIsProcessing(false)
{
	ui.setupUi(this);
	//���ù�����
	ui.mainToolBar->addAction(ui.acReadVideo);
	ui.mainToolBar->addAction(ui.acStartDetect);
	//����״̬��
	uStatusLabel = new QLabel();
	uStatusLabel->setMinimumSize(uStatusLabel->sizeHint());
	uStatusLabel->setAlignment(Qt::AlignHCenter);
	this->statusBar()->addWidget(uStatusLabel);
	//���ø���������״̬����ʾ��Ϣ
	ui.acReadVideo->setStatusTip(tr("��һ����Ƶ�ļ�"));
	ui.acStartDetect->setStatusTip(tr("��ʼ���е��߼��"));
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
	delete mDenoiseProcessor;
}


void MainWindow::on_acReadVideo_triggered()
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
	displayMat(mInputMat, ui.labelInputFrame, ui.frameInputBox);

	mReady2PalyVideo = true;

}


void MainWindow::on_acExit_triggered()
{
	if (!(QMessageBox::information(this,tr("�˳�"),tr("���Ҫ�˳�������"),tr("��"),tr("��"))))
	{
		this->close();
	}
}


void MainWindow::on_acStartDetect_triggered()
{
	if (!mReady2PalyVideo)
	{
		mUnexpectedActionHandler.handle(UnexpectedActionHandler::OPEN_FILE_FAILURE);
		return;
	}

	double videoRate = mVideoCapture.get(CV_CAP_PROP_FPS);
	int delayBetween2Frames = 1000/videoRate;

	mQTimer->start(delayBetween2Frames);
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
		//ֹͣ��ʱ��
		mQTimer->stop();
		ui.labelInputFrame->setText(tr("                    ��Ƶ���Ž�����"));
		//�ͷ���Ƶ��Դ
		mVideoCapture.release();
	}
}

void MainWindow::displayDenoisedMat()
{
	mDenoiseProcessor->process(mInputMat, mDenoiseMat);
	displayMat(mDenoiseMat, ui.labelDenoiseFrame, ui.frameDenoiseBox);
}

void MainWindow::displaySegedMat()
{
	mSegmentProcessor->process(mDenoiseMat, mSegmentMat, mMorpgMat,coordinates, rotatedRects);
	displayMat(mSegmentMat, ui.labelSegmentFrame, ui.frameSegmentBox);
	displayMat(mMorpgMat, ui.labelMorphFrame, ui.frameMorphBox);
}

void MainWindow::displayOutputMat()
{
//	mOutputMat = mInputMat;
	displayMat(mOutputMat, ui.labelOutputFrame, ui.frameOutputBox);
}

void MainWindow::totalProcess()
{
	//��֮ǰ֡û�д����꣬��������֡
	if ( !mIsProcessing )
	{
		mIsProcessing = true;
		displayInputMat();
		displayDenoisedMat();
		displaySegedMat();
		displayOutputMat();
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
		mDenoiseProcessor->setDenoiseStrategy(DoublehistEqual::getInstance());		break;
	case 3:
		mDenoiseProcessor->setDenoiseStrategy(FD::getInstance());		break;
	case 4:
		mDenoiseProcessor->setDenoiseStrategy(MaxMedianFilter::getInstance());		break;
	case 5:
		mDenoiseProcessor->setDenoiseStrategy(BaseWeightBGP::getInstance());		break;
	case 6:
		mDenoiseProcessor->setDenoiseStrategy(TDLMS::getInstance());		break;
	case 7:
		mDenoiseProcessor->setDenoiseStrategy(LMPM::getInstance());		break;
	case 8:
		mDenoiseProcessor->setDenoiseStrategy(LocalMeanContrast::getInstance());		break;
	case 9:
		mDenoiseProcessor->setDenoiseStrategy(Localshannon::getInstance());		break;
	case 10:
		mDenoiseProcessor->setDenoiseStrategy(Localstd::getInstance());		break;
	case 11:
		mDenoiseProcessor->setDenoiseStrategy(Pmdiff1::getInstance());		break;
	case 12:
		mDenoiseProcessor->setDenoiseStrategy(Pmdiff2::getInstance());		break;
	case 13:
		mDenoiseProcessor->setDenoiseStrategy(Pmdiffmy::getInstance());		break;
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
		mSegmentProcessor->setSegmentStrategy(DefaultSegmentStrategy::getInstance());
		break;
	default:
		mSegmentProcessor->setSegmentStrategy(DefaultSegmentStrategy::getInstance());
		break;
	}
}












