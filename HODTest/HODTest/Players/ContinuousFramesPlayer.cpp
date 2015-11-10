#include "./Players/ContinuousFramesPlayer.h"
#include <iostream>


ContinuousFramesPlayer::ContinuousFramesPlayer(void) : mCurrentFrame(0)
{
}


ContinuousFramesPlayer::~ContinuousFramesPlayer(void)
{
}

bool ContinuousFramesPlayer::readVideo(const string& filepath)
{

	string filename = filepath + "\\ºÁÃ×²¨_1.jpg";
	std::cout << filename;

	return false;
}

void ContinuousFramesPlayer::getNextFrame(Mat&)
{

}

void ContinuousFramesPlayer::releaseVideo()
{

}

bool ContinuousFramesPlayer::videoIsOver()
{
	return false;
}
