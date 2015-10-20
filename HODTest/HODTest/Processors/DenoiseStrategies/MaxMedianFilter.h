#pragma once
#include "./Processors/DenoiseStrategy.h"

//最大中值滤波
class MaxMedianFilter : public DenoiseStrategy
{
public:

	~MaxMedianFilter(void) {}

	static MaxMedianFilter* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new MaxMedianFilter();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	MaxMedianFilter(void) {}
	static MaxMedianFilter* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(MaxMedianFilter::mSingleton)  
				delete MaxMedianFilter::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void maxmedianfilter(unsigned char* image, int height, int width);
};
