#pragma once
#include "./Processors/DenoiseStrategy.h"

//基于局部熵背景抑制
class Localshannon : public DenoiseStrategy
{
public:

	~Localshannon(void) {}

	static Localshannon* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Localshannon();
		}
		return mSingleton;
	}

	//核心处理函数
	void denoise(const Mat& srcImg, Mat& desImg);
	void setKsize(int ksize) { mKsize = ksize; }

private:
	Localshannon(void) : mKsize(5){}
	static Localshannon* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(Localshannon::mSingleton)  
				delete Localshannon::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void localshannon(unsigned char *image, int width, int height, int LL);
	int mKsize;
};
