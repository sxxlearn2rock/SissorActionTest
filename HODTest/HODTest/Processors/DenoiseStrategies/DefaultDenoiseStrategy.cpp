#include "DefaultDenoiseStrategy.h"


//�ྲ̬����������.cpp�ļ�������
DefaultDenosieStrategy*	DefaultDenosieStrategy::mSingleton = NULL;

void DefaultDenosieStrategy::denoise(const Mat& srcImg, Mat& desImg)
{
	cv::cvtColor(srcImg, desImg, CV_BGR2GRAY);
}



