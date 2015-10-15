#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include "UnexpectedActionHandler.h"

#include "ProcessorFactory.h"
#include "DenoiseStrategy.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QtGui/QMainWindow>
#include <QtGui/QImage>
#include <QtCore/QTimer>

using cv::Mat; using cv::VideoCapture;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	bool mReady2PalyVideo;
	bool mStopPlayVideo;

	Ui::MainWindowClass ui;
	VideoCapture mVideoCapture;
	UnexpectedActionHandler mUnexpectedActionHandler;

	Mat mInputMat;
	Mat mDenoiseMat;
	Mat mSegmentMat;
	Mat mRecogniseMat;
	Mat mOutputMat;

	QTimer* mQTimer;


	//三个核心图像处理器
	DenoiseProcessor* mDenoiseProcessor;
	//SegmentProcessor* mSegmentProcessor;
	//RecogniseProcessor* mRecogniseProcessor;

	void displayMat(cv::Mat&, QLabel*, QFrame*);
	void displayInputMat();
	void displayDenoisedMat();
	void displayOutputMat();
	void setDenoiseStrategy(int index);

signals:
	

private slots:
	void on_acReadVideo_triggered();
	void on_acExit_triggered();
	void on_btnStartDetect_clicked();
	
	void on_comboDenoise_currentIndexChanged();
	void totalProcess();


};

#endif // MAINWINDOW_H
