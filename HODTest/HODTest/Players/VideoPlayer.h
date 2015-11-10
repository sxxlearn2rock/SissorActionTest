#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <QString>

using std::string;
using cv::Mat;

class VideoPlayer
{
public:
	VideoPlayer(void) : mCurrentFrameNo(0) {}
	~VideoPlayer(void) {}
//	virtual bool readVideo(const string& filepath) = 0;
	virtual bool readVideo(const QString& filepath) = 0;
	virtual bool getNextFrame(Mat& ) = 0;
	virtual void releaseVideo() = 0;
	virtual double getVideoRate() { return 5; }

	long getCurrentFramNo() { return mCurrentFrameNo; }
protected:
	long mCurrentFrameNo;
};

