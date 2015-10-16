#include "SegmentProcessor.h"

SegmentProcessor* SegmentProcessor::mSingleton = NULL;

//����Ĵ����߼����ɾ���Ĳ�����������
void SegmentProcessor::process(Mat& srcImg, Mat& desImg, Mat& segImg,
	vector<Coordinate> coordinates, vector<RotatedRect> rotatedRects)
{
	mSegmentStrategy->process(srcImg, segImg, desImg, coordinates, rotatedRects);
}
