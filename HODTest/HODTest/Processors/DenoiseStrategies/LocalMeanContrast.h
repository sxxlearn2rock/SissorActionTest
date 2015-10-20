#pragma once
#include "./Processors/DenoiseStrategy.h"

//基于局部均值对比度背景抑制
class LocalMeanContrast : public DenoiseStrategy
{
public:

	~LocalMeanContrast(void) {}

	static LocalMeanContrast* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new LocalMeanContrast();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

	void setKsize(int ksize1 , int ksize2) 
	{
		mKsize1 = ksize1; 
		mKsize2 = ksize2; 
	}

private:
	LocalMeanContrast(void) : mKsize1(5) , mKsize2(11){}
	static LocalMeanContrast* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(LocalMeanContrast::mSingleton)  
				delete LocalMeanContrast::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void localmeancontrast(unsigned char* image, int height, int width, int Ksize1, int Ksize2);
	int mKsize1;
	int mKsize2;
};


