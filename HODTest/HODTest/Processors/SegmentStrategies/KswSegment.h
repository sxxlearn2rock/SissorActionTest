#pragma once
#include "./Processors/SegmentStrategy.h"

//����ģʽ
class KswSegment  : public SegmentStrategy
{
public:
	~KswSegment(void) {}
	static KswSegment* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new KswSegment();
		}
		return mSingleton;
	}

	void process(Mat& srcImg, Mat& segImg, Mat& desImg, vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects);

private:
	KswSegment(void)  {}
	static KswSegment* mSingleton;

	class Cleaner
	{
	public:
		~Cleaner()
		{
			if (KswSegment::mSingleton != NULL)
			{
				delete KswSegment::mSingleton;
			}
		}
	};
	static Cleaner cleaner;

	//����Ϊ˽�к���
	Mat histCalculate(const Mat& src);
	float calEntropy(const Mat& hist, int threshold);
	void maxEntropy(Mat srcImg, Mat& dstImg, Mat hist);

};

