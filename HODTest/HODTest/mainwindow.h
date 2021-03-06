#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include "UnexpectedActionHandler.h"

#include "DenoiseProcessor.h"
#include "SegmentProcessor.h"
#include "./Processors/DenoiseStrategy.h"
#include "./Processors/SegmentStrategy.h"

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QtGui/QMainWindow>
#include <QtGui/QImage>
#include <QtCore/QTimer>

using std::vector;
using cv::Mat; using cv::VideoCapture; using cv::RotatedRect;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	//UI相关的成员变量，以u为前缀
	QLabel* uStatusLabel;

	bool mReady2Process;
	bool mStopPlayVideo;
	bool mIsProcessing;
	bool mVideoIsOver;
	bool mIsVideoMode;

	Ui::MainWindowClass ui;
	VideoCapture mVideoCapture;
	UnexpectedActionHandler mUnexpectedActionHandler;

	//各个阶段的图像
	Mat mInputMat;
	Mat mDenoiseMat;
	Mat mSegmentMat;
	Mat mMorphMat;
	Mat mRecogniseMat;
	Mat mOutputMat;

	//定时器，用以固定帧率显示图像，形成视频播放效果
	QTimer* mQTimer;

	//三个核心图像处理器
	DenoiseProcessor* mDenoiseProcessor;
	SegmentProcessor* mSegmentProcessor;
	//RecogniseProcessor* mRecogniseProcessor;

	//保存输出目标的质心坐标
	vector<Coordinate> coordinates;
	//保存输出目标的外围旋转矩形
	vector<RotatedRect> rotatedRects;

	void displayMat(cv::Mat&, QLabel*, QFrame*);
	void displayInputMat();
	void displayDenoisedMat();
	void displaySegedMat();
	void displayOutputMat();
	void clearAllFrame();
	void releaseResource();

	void setDenoiseStrategy(int index);
	void setSegmentStrategy(int index);

signals:
	
private slots:
	void on_acReadVideo_triggered();
	void on_acReadPic_triggered();
	void on_acExit_triggered();
	void on_acStartDetect_triggered();
	void on_acStartDetectPic_triggered();
	void on_comboDenoise_currentIndexChanged();
	void on_comboSegment_currentIndexChanged();

	void totalProcess();

};

#endif // MAINWINDOW_H
