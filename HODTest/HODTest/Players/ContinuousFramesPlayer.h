#pragma once
#include "VideoPalyer.h"

//用以播放连续帧的播放器
class ContinuousFramesPlayer : public VideoPlayer
{
public:
	ContinuousFramesPlayer(void);
	~ContinuousFramesPlayer(void);
};

