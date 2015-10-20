#pragma once
#include "./Processors/SegmentStrategy.h"
#include "./Processors/strategies.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//µ¥ÀýÄ£Ê½
class SegmentProcessor
{
public:
	~SegmentProcessor(void) {}
	static SegmentProcessor* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new SegmentProcessor;
		}
		return mSingleton;
	}

	void setSegmentStrategy(SegmentStrategy* strategy) { mSegmentStrategy = strategy; }

	void process(Mat& srcImg, Mat& segImg, Mat& desImg, 
		vector<Coordinate> coordinates, vector<RotatedRect> rotatedRects);
private:
		SegmentProcessor(void) {}
		SegmentProcessor(SegmentStrategy* strategy) { mSegmentStrategy = strategy; }
		static SegmentProcessor* mSingleton;

		class Cleaner
		{
		public:
			~Cleaner()
			{
				if (SegmentProcessor::mSingleton != NULL)
				{
					delete SegmentProcessor::mSingleton;
				}
			}
		};
		static Cleaner cleaner;

		SegmentStrategy* mSegmentStrategy;
};

