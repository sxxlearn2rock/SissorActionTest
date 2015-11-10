#pragma once
#include "VideoPlayer.h"

//用以播放连续帧的播放器
class ContinuousFramesPlayer : public VideoPlayer
{
public:
	ContinuousFramesPlayer(void);
	~ContinuousFramesPlayer(void);

	bool readVideo(const string& filepath);
	void getNextFrame(Mat& );
	bool videoIsOver();
	void releaseVideo();
private:
	long mCurrentFrame;
	string mPreName;
	string mExtName;
};

