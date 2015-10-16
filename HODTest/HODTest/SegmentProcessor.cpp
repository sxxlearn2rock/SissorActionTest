#include "SegmentProcessor.h"

SegmentProcessor* SegmentProcessor::mSingleton = NULL;

//具体的处理逻辑交由具体的策略类来处理
void SegmentProcessor::process(Mat& srcImg, Mat& desImg, 
	vector<Coordinate> coordinates, vector<RotatedRect> rotatedRects)
{
	mSegmentStrategy->process(srcImg, desImg, coordinates, rotatedRects);
}
