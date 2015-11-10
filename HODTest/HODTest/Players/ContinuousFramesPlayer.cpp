#include "./Players/ContinuousFramesPlayer.h"
#include <iostream>
#include <QTextCodec>
#include <qdebug.h>


ContinuousFramesPlayer::ContinuousFramesPlayer(void) : mTotalFrames(0)
{
	mPreName = QObject::tr("���ײ�_");
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
	//filter.append("���ײ�_*.jpg");
	//QList<QString> *fileInfo=new QList<QString>(dir.entryList(filter));

	//for (int i = 0; i < fileInfo->size(); ++i)
	//{
	//	cout << fileInfo->at(i) << std::endl;
	//}
	////string filename = filepath + "\\���ײ�_1.jpg";
	////std::cout << filename;

	//return false;
//}

bool ContinuousFramesPlayer::readVideo(const QString& filepath)
{
	mCurrentDir = filepath;
	QDir dir(filepath);
	QStringList filter;
	filter.append(mPreName + "*." + mExtName);

	//��ȡ�����ļ������Ϲ淶���ļ�����Ϣ
	filesInfo =new QList<QFileInfo>(dir.entryInfoList(filter,QDir::Files));
	mTotalFrames = filesInfo->size();

	return (mTotalFrames > 0);
}

bool ContinuousFramesPlayer::getNextFrame(Mat& img)
{
	Mat temp;
	QString filename; 

	//��whileѭ����Ϊ������ȱʧ֡��ʱ��������ȱʧ֡����
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

