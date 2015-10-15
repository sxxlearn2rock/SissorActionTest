#include "TestDenoiseStrategy.h"

TestDenoiseStrategy* TestDenoiseStrategy::mSingleton = NULL;

void TestDenoiseStrategy::denoise(const Mat& srcImg, Mat& desImg)
{
	cv::Mat ele(mArg, mArg, CV_8U,cv::Scalar(1));
	cv::morphologyEx(srcImg, desImg, cv::MORPH_OPEN, ele);
}
