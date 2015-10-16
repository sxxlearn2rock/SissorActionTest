#include "DefaultSegmentStrategy.h"
DefaultSegmentStrategy* DefaultSegmentStrategy::mSingletion = NULL;

void DefaultSegmentStrategy::process(Mat& srcImg, Mat& desImg, Mat& segImg,
	vector<Coordinate> coordinates, vector<RotatedRect> rotatedRects)
{
	desImg = srcImg;
}
