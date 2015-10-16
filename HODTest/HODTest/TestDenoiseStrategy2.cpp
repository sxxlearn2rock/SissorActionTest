#include "TestDenoiseStrategy2.h"

TestDenoiseStrategy2* TestDenoiseStrategy2::mSingleton = NULL;

void TestDenoiseStrategy2::denoise(const Mat& srcImg, Mat& desImg)
{
	cv::Mat ele(mArg, mArg, CV_8U,cv::Scalar(1));
	cv::morphologyEx(srcImg, desImg, cv::MORPH_CLOSE, ele);
}
