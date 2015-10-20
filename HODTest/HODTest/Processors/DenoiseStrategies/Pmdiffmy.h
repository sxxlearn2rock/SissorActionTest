#pragma once
#include "./Processors/DenoiseStrategy.h"

//改进型各项异性滤波
class Pmdiffmy : public DenoiseStrategy
{
public:

	~Pmdiffmy(void) {}

	static Pmdiffmy* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Pmdiffmy();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	Pmdiffmy(void) {}
	static Pmdiffmy* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(Pmdiffmy::mSingleton)  
				delete Pmdiffmy::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void pmdiffmy(unsigned char* image, int height, int width);
};
