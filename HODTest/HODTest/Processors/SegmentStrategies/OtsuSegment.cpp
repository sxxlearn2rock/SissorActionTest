#include "./Processors/SegmentStrategies/OtsuSegment.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using cv::Mat;

OtsuSegment* OtsuSegment::mSingleton = NULL;

void OtsuSegment::process( Mat& srcImg, Mat& segImg, Mat& desImg, vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects )
{
	thresholdOtsu(srcImg, segImg);
	morphFilter(segImg, desImg, mErosionType, mDilationType, mErosionSize, mDilationSize);
	positionResult(desImg, desImg, coordinates, rotatedRects);
}

void OtsuSegment::thresholdOtsu( Mat src, Mat& dst )
{
	int width = src.cols * src.channels();
	int height = src.rows;	

	//histogram
	float histogram[256] = {0};
	for(int i = 0; i < height; i++) {
		unsigned char *p = src.ptr<unsigned char>(i);
		for(int j = 0; j < width; j++) 
		{
			histogram[*p++]++;
		}
	}
	//normalize histogram
	int size = height * width;
	for(int i = 0;i < 256;i++) {
		histogram[i]=histogram[i] / size;
	}

	//average pixel value
	float avgValue=0;
	for(int i=0;i<256;i++) {
		avgValue+=i*histogram[i];
	}

	int threshold;	
	float maxVariance=0;
	float w=0,u=0;
	for(int i=0;i<256;i++) {
		w+=histogram[i];
		u+=i*histogram[i];

		float t=avgValue*w-u;
		float variance=t*t/(w*(1-w));
		if(variance>maxVariance) {
			maxVariance=variance;
			threshold=i;
		}
	}
	cv::threshold(src,dst,threshold,255,cv::THRESH_BINARY);
}

