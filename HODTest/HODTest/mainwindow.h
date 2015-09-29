#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include "UnexpectedActionHandler.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QtGui/QMainWindow>
#include <QtGui/QImage>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	Ui::MainWindowClass ui;
	cv::VideoCapture mVideoCapture;
	UnexpectedActionHandler mUnexpectedActionHandler;

	cv::Mat mInputMat;
	cv::Mat mOutputMat;

	void displayMat(cv::Mat& image);

private slots:
	void on_acOpenVideo_triggered();
	void on_acExit_triggered();

};

#endif // MAINWINDOW_H
