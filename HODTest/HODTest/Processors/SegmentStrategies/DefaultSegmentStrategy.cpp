#include "./Processors/SegmentStrategies/DefaultSegmentStrategy.h"
DefaultSegmentStrategy* DefaultSegmentStrategy::mSingletion = NULL;

void DefaultSegmentStrategy::process(Mat& srcImg, Mat& segImg, Mat& desImg, 
	vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects)
{
	segImg = srcImg.clone();
	desImg = srcImg.clone();
}