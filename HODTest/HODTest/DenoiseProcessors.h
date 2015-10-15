#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using cv::Mat;


class DenoiseProcessor
{
public:
	DenoiseProcessor(void) {}
	~DenoiseProcessor(void) {}

	virtual void denoise(const Mat& srcImg, Mat& desImg) = 0;
};

class DefaultDenosieProcessor : public DenoiseProcessor
{
public:
	DefaultDenosieProcessor(void) {}
	~DefaultDenosieProcessor(void) {}

	void denoise(const Mat& srcImg, Mat& desImg);
protected:
private:
};