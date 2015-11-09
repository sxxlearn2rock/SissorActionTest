#include "./Players/VideoFilePlayer.h"

#include <QString>
#include <QObject>
#include <QtGui/QFileDialog>

VideoFilePlayer::VideoFilePlayer(void)
{
}


VideoFilePlayer::~VideoFilePlayer(void)
{
	releaseVideo();
}

bool VideoFilePlayer::readVideo(const string& fileName)
{	
	mVideoCapture.open(fileName);
	return mVideoCapture.isOpened();
}

void VideoFilePlayer::getNextFrame(Mat& frameMat)
{
	mVideoCapture.read(mCurrentMat);
	frameMat = mCurrentMat;
}

double VideoFilePlayer::getVideoRate()
{
	return mVideoCapture.get(CV_CAP_PROP_FPS);
}

bool VideoFilePlayer::videoIsOver()
{
	return !mCurrentMat.data;
}

void VideoFilePlayer::releaseVideo()
{
	mVideoCapture.release();
}
