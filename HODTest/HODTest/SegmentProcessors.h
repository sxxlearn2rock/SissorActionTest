#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::vector;
using cv::Mat;	using cv::Rect;

class SegmentProcessor
{
public:
	SegmentProcessor(void) {}
	~SegmentProcessor(void) {}

	virtual void segment(Mat& srcImg, Mat& desImg, vector<Rect> segAreas) = 0;
};

class DefaultSegmentProcessor : public SegmentProcessor
{
public:
	DefaultSegmentProcessor(void) {}
	~DefaultSegmentProcessor(void) {}
	void segment(Mat& srcImg, Mat& desImg, vector<Rect> segAreas);
protected:
private:
};