#pragma once
#include "VideoPlayer.h"
#include <QDir>
#include <QString>
#include <QList>

//用以播放连续帧的播放器
class ContinuousFramesPlayer : public VideoPlayer
{
public:
	ContinuousFramesPlayer(void);
	~ContinuousFramesPlayer(void);

//	bool readVideo(const string& filepath);
	bool readVideo(const QString& filepath);
	bool getNextFrame(Mat& );
	void releaseVideo();
private:
	long mTotalFrames;
	QString mCurrentDir;
	QString mPreName;
	QString mExtName;
	QList<QFileInfo> *filesInfo;

};

