#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include "UnexpectedActionHandler.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QtGui/QMainWindow>
#include <QtGui/QImage>
#include <QtCore/QTimer>


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
	cv::VideoCapture mVideoCapture;
	UnexpectedActionHandler mUnexpectedActionHandler;

	cv::Mat mInputMat;
	QImage mInputQImage;
	cv::Mat mOutputMat;

	QTimer *mQTimer;

	void displayMat(cv::Mat& image);
	void delay(int seconds);
	void displayInputVideo();

signals:
	

private slots:
	void on_acOpenVideo_triggered();
	void on_acExit_triggered();
	void on_btnStartDetect_clicked();
	void displayInputMat();

};

#endif // MAINWINDOW_H
