#pragma once
#include "VideoPalyer.h"

//视频文件播放器，用以播放单独的视频文件
class VideoFilePlayer : VideoPlayer
{
public:
	VideoFilePlayer(void);
	~VideoFilePlayer(void);
	readVideo(const string& filepath)
};

