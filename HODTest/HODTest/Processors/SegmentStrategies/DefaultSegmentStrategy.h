#pragma once
#include "./Processors/SegmentStrategy.h"

//µ¥ÀýÄ£Ê½
class DefaultSegmentStrategy : public SegmentStrategy
{
public:
	~DefaultSegmentStrategy(void) {}
	static DefaultSegmentStrategy* getInstance()
	{
		if (mSingletion == NULL)
		{
			mSingletion = new DefaultSegmentStrategy();
		}
		return mSingletion;
	}

	void process(Mat& srcImg, Mat& segImg, Mat& desImg, 
		vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects) ;

private:
	DefaultSegmentStrategy(void) {}
	static DefaultSegmentStrategy* mSingletion;

	class Cleaner 
	{
	public:
		~Cleaner()
		{
			if (DefaultSegmentStrategy::mSingletion)
			{
				delete DefaultSegmentStrategy::mSingletion;
			}
		}
	};
	static Cleaner cleaner;
};

