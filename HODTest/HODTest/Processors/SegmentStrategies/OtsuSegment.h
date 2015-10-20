#pragma once
#include "./Processors/SegmentStrategy.h"

//单例模式
class OtsuSegment  : public SegmentStrategy
{
public:
	~OtsuSegment(void) {}
	static OtsuSegment* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new OtsuSegment();
		}
		return mSingleton;
	}

	void process(Mat& srcImg, Mat& segImg, Mat& desImg, vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects);

private:
	OtsuSegment(void)  {}
	static OtsuSegment* mSingleton;

	class Cleaner
	{
	public:
		~Cleaner()
		{
			if (OtsuSegment::mSingleton != NULL)
			{
				delete OtsuSegment::mSingleton;
			}
		}
	};
	static Cleaner cleaner;

	//以下为私有函数
	void thresholdOtsu(Mat src, Mat &dst);
};
