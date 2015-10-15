#include "DefaultDenoiseProcessor.h"

//静态变量必须在.cpp文件里声明
DefaultDenosieProcessor*	DefaultDenosieProcessor::mSingleton = NULL;

void DefaultDenosieProcessor::denoise(const Mat& srcImg, Mat& desImg)
{
	cv::Mat ele(10,10,CV_8U,cv::Scalar(1));
	cv::morphologyEx(srcImg, desImg, cv::MORPH_CLOSE, ele);

	//		cv::erode(srcImg, desImg, cv::Mat());

	//		cv::Canny(srcImg, desImg, 125, 350);
}



