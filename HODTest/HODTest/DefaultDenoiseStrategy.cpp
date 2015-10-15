#include "strategies.h"

//静态变量必须在.cpp文件里声明
DefaultDenosieStrategy*	DefaultDenosieStrategy::mSingleton = NULL;

void DefaultDenosieStrategy::denoise(const Mat& srcImg, Mat& desImg)
{
	cv::Mat ele(mArg1, mArg1, CV_8U,cv::Scalar(1));
	cv::morphologyEx(srcImg, desImg, cv::MORPH_CLOSE, ele);
}



