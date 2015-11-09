#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include "UnexpectedActionHandler.h"

#include "./Players/VideoPlayer.h"
#include "./Players/VideoFilePlayer.h"
#include "./Players/ContinuousFramesPlayer.h"

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

enum Mode {FRAMES,	VIDEO};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	//UI��صĳ�Ա��������uΪǰ׺
	QLabel* uStatusLabel;

	Mode mProcessMode;

	bool mReady2PalyVideo;
	bool mStopPlayVideo;
	bool mIsProcessing;

	Ui::MainWindowClass ui;
//	VideoCapture mVideoCapture;
	VideoPlayer* mVideoPlayer;

	UnexpectedActionHandler mUnexpectedActionHandler;

	//�����׶ε�ͼ��
	Mat mInputMat;
	Mat mDenoiseMat;
	Mat mSegmentMat;
	Mat mMorphMat;
	Mat mRecogniseMat;
	Mat mOutputMat;

	//��ʱ�������Թ̶�֡����ʾͼ���γ���Ƶ����Ч��
	QTimer* mQTimer;

	//��������ͼ������
	DenoiseProcessor* mDenoiseProcessor;
	SegmentProcessor* mSegmentProcessor;
	//RecogniseProcessor* mRecogniseProcessor;

	//�������Ŀ�����������
	vector<Coordinate> coordinates;
	//�������Ŀ�����Χ��ת����
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
	void on_acReadContinuousFrames_triggered();
	void on_acReadVideo_triggered();
	void on_acExit_triggered();
	void on_acStartDetect_triggered();
	void on_comboDenoise_currentIndexChanged();
	void on_comboSegment_currentIndexChanged();

	void totalProcess();

};

#endif // MAINWINDOW_H
