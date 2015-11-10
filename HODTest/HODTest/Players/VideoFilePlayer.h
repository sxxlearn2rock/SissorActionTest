#pragma once
#include "VideoPlayer.h"

//视频文件播放器，用以播放单独的视频文件
class VideoFilePlayer : public VideoPlayer
{
public:
	VideoFilePlayer(void);
	~VideoFilePlayer(void);

//	bool readVideo(const string& filepath);
	bool readVideo(const QString& filepath);
	bool getNextFrame(Mat&);
	double getVideoRate();
	void releaseVideo();
private:
	cv::VideoCapture mVideoCapture;
	cv::Mat mCurrentMat;
};

