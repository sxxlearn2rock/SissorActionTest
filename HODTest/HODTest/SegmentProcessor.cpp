#include "SegmentProcessor.h"

SegmentProcessor* SegmentProcessor::mSingleton = NULL;

//����Ĵ����߼����ɾ���Ĳ�����������
void SegmentProcessor::process(Mat& srcImg, Mat& desImg, 
	vector<Coordinate> coordinates, vector<RotatedRect> rotatedRects)
{
	mSegmentStrategy->process(srcImg, desImg, coordinates, rotatedRects);
}
