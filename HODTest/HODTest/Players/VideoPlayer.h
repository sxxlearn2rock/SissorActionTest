#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>

using std::string;
using cv::Mat;

class VideoPlayer
{
public:
	VideoPlayer(void) {}
	~VideoPlayer(void) {}
	virtual bool readVideo(const string& filepath) = 0;
	virtual void getNextFrame(Mat& ) = 0;
	virtual bool videoIsOver() = 0;
	virtual void releaseVideo() = 0;
	virtual double getVideoRate() { return 24; }
};