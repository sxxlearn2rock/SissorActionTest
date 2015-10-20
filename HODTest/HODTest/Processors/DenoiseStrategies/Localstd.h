#pragma once
#include "./Processors/DenoiseStrategy.h"

//基于局部方差背景抑制
class Localstd : public DenoiseStrategy
{
public:

	~Localstd(void) {}

	static Localstd* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Localstd();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

	void setKsize(int ksize) { mKsize = ksize; }
private:
	Localstd(void) : mKsize(5){}
	static Localstd* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(Localstd::mSingleton)  
				delete Localstd::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void localstd(unsigned char* image, int height, int width, int Ksize);
	int mKsize;
};
