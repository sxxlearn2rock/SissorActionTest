#pragma once
#include "./Processors/DenoiseStrategy.h"

//直方图双向均衡增强
class DoublehistEqual : public DenoiseStrategy
{
public:

	~DoublehistEqual(void) {}

	static DoublehistEqual* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DoublehistEqual();
		}
		return mSingleton;
	}

	//核心处理函数
	void denoise(const Mat& srcImg, Mat& desImg);
private:
	DoublehistEqual(void) {}
	static DoublehistEqual* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(DoublehistEqual::mSingleton)  
				delete DoublehistEqual::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void histEqual2(unsigned char *image, int height, int width );
	void imfilter(float *pimgsorce, float *image1, int width, int height, int *moban);
};
