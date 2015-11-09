#pragma once
#include <string>

using std::string;
//视频播放器的超类，规定所有视频播放器的标准
abstract class VideoPlayer
{
public:
	virtual void readVideo(const std::string& filepath) = 0;

};