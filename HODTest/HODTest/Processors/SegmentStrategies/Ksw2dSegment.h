#pragma once
#include "./Processors/SegmentStrategy.h"

//µ¥ÀýÄ£Ê½
class Ksw2dSegment  : public SegmentStrategy
{
public:
	~Ksw2dSegment(void) {}
	static Ksw2dSegment* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Ksw2dSegment();
		}
		return mSingleton;
	}

	void process(Mat& srcImg, Mat& segImg, Mat& desImg, vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects);



private:
	Ksw2dSegment(void)  {}
	static Ksw2dSegment* mSingleton;

	class Cleaner
	{
	public:
		~Cleaner()
		{
			if (Ksw2dSegment::mSingleton != NULL)
			{
				delete Ksw2dSegment::mSingleton;
			}
		}
	};
	static Cleaner cleaner;

	void ksw2dSegmentation(unsigned char* image,int width,int height);
};

