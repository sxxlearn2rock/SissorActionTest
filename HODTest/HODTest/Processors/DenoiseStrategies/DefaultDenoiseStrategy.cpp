#include "DefaultDenoiseStrategy.h"

//类静态变量必须在.cpp文件里声明
DefaultDenosieStrategy*	DefaultDenosieStrategy::mSingleton = NULL;

void DefaultDenosieStrategy::denoise(Mat& srcImg, Mat& desImg)
{


	cv::cvtColor(srcImg, desImg, CV_BGR2GRAY);
//	imshow("gray", desImg);

}



