#pragma once
#include "./Processors/DenoiseStrategy.h"

//单例模式
class Pmdiff2 : public DenoiseStrategy
{
public:

	~Pmdiff2(void) {}

	static Pmdiff2* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Pmdiff2();
		}
		return mSingleton;
	}

	//核心处理函数
	void denoise( Mat& srcImg, Mat& desImg);
private:
	Pmdiff2(void) {}
	static Pmdiff2* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(Pmdiff2::mSingleton)  
				delete Pmdiff2::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void pm(unsigned char *image, int height, int width );
	void imfilter(float *pimgsorce, float *image1, int width, int height, int *moban);
};
