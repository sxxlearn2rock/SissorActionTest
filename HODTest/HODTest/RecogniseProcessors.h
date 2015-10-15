#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::vector;
using cv::Mat;	using cv::Rect;

class RecogniseProcessor
{
public:
	RecogniseProcessor(void) {}
	~RecogniseProcessor(void) {}

	virtual void recognise() = 0;
};
