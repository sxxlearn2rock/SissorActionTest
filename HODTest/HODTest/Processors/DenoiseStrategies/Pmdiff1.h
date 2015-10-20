#pragma once
#include "./Processors/DenoiseStrategy.h"

//一维各项异性滤波
class Pmdiff1 : public DenoiseStrategy
{
public:

	~Pmdiff1(void) {}

	static Pmdiff1* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Pmdiff1();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	Pmdiff1(void) {}
	static Pmdiff1* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(Pmdiff1::mSingleton)  
				delete Pmdiff1::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void pmdiff1(unsigned char* image, int height, int width);
};
