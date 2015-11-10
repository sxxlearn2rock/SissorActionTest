#include "./Players/VideoFilePlayer.h"

#include <QString>
#include <QObject>
#include <QTextCodec>
#include <QtGui/QFileDialog>

VideoFilePlayer::VideoFilePlayer(void)
{
}


VideoFilePlayer::~VideoFilePlayer(void)
{
	releaseVideo();
}

//bool VideoFilePlayer::readVideo(const string& fileName)
//{	
//	mVideoCapture.open(fileName);
//	return mVideoCapture.isOpened();
//}

bool VideoFilePlayer::readVideo(const QString& filepath)
{
	//��QStringת��Ϊ��׼string�����ҿ���ʶ������
	mVideoCapture.open((QTextCodec::codecForName("GB18030")->fromUnicode(filepath).data()));
	return mVideoCapture.isOpened();
}

bool VideoFilePlayer::getNextFrame(Mat& frameMat)
{
	if (mVideoCapture.read(frameMat))
	{
		mCurrentFrameNo++;
//		frameMat = mCurrentMat;
		return true;
	}
	return false;
}

double VideoFilePlayer::getVideoRate()
{
	return mVideoCapture.get(CV_CAP_PROP_FPS);
}

void VideoFilePlayer::releaseVideo()
{
	mCurrentFrameNo = 0;
	mVideoCapture.release();
}
