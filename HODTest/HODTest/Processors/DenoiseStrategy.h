#pragma once
#include "DenoiseStrategy.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using cv::Mat;

//����ȥ����Եĸ���
class DenoiseStrategy
{
public:
	DenoiseStrategy(void) {}
	~DenoiseStrategy(void) {}

	virtual void denoise(const Mat& srcImg, Mat& desImg) = 0;
};

