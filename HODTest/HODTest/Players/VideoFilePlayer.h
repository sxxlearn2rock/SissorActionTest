#pragma once
#include "VideoPlayer.h"

//��Ƶ�ļ������������Բ��ŵ�������Ƶ�ļ�
class VideoFilePlayer : public VideoPlayer
{
public:
	VideoFilePlayer(void);
	~VideoFilePlayer(void);

	bool readVideo(const string& filepath);
	void getNextFrame(Mat&);
	double getVideoRate();
	void releaseVideo();
	bool videoIsOver();
private:
	cv::VideoCapture mVideoCapture;
	cv::Mat mCurrentMat;
};

