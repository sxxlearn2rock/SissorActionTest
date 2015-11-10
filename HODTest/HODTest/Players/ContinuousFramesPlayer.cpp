#include "./Players/ContinuousFramesPlayer.h"
#include <iostream>
#include <QTextCodec>
#include <qdebug.h>


ContinuousFramesPlayer::ContinuousFramesPlayer(void) : mTotalFrames(0)
{
	mPreName = QObject::tr("毫米波_");
	mExtName = QObject::tr("jpg");
	filesInfo = new QList<QFileInfo>();
}


ContinuousFramesPlayer::~ContinuousFramesPlayer(void)
{
}

//bool ContinuousFramesPlayer::readVideo(const string& filepath)
//{
	////	QFileInfo fileInfo(filepath);
	//QDir dir(filepath);
	//QStringList filter;
	//filter.append("毫米波_*.jpg");
	//QList<QString> *fileInfo=new QList<QString>(dir.entryList(filter));

	//for (int i = 0; i < fileInfo->size(); ++i)
	//{
	//	cout << fileInfo->at(i) << std::endl;
	//}
	////string filename = filepath + "\\毫米波_1.jpg";
	////std::cout << filename;

	//return false;
//}

bool ContinuousFramesPlayer::readVideo(const QString& filepath)
{
	mCurrentDir = filepath;
	QDir dir(filepath);
	QStringList filter;
	filter.append(mPreName + "*." + mExtName);

	//读取所有文件名符合规范的文件的信息
	filesInfo =new QList<QFileInfo>(dir.entryInfoList(filter,QDir::Files));
	mTotalFrames = filesInfo->size();

	return (mTotalFrames > 0);
}

bool ContinuousFramesPlayer::getNextFrame(Mat& img)
{
	Mat temp;
	QString filename; 

	//此while循环是为了在有缺失帧的时候能跳过缺失帧播放
// 	while (mCurrentFrameNo++ < mTotalFrames)
// 	{
// 		filename = mCurrentDir + QObject::tr("\\%1%2.%3").arg(mPreName).arg(mCurrentFrameNo).arg(mExtName);
// 		temp = cv::imread(QTextCodec::codecForName("GB18030")->fromUnicode(filename).data());
// 		if ( temp.data)
// 		{
// 			img = temp;
// 			return true;
// 		}
// 	}

	return false;
}

void ContinuousFramesPlayer::releaseVideo()
{
//	mCurrentFrameNo = 0;
}

