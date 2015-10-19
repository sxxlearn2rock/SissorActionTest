#pragma once
#include "./Processors/DenoiseStrategy.h"

//单例模式
class LateralInhibition : public DenoiseStrategy
{
public:

	~LateralInhibition(void) {}

	static LateralInhibition* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new LateralInhibition();
		}
		return mSingleton;
	}


	void denoise( Mat& srcImg, Mat& desImg);

	void setKsize(int ksize) { mKsize = ksize; }
private:
	LateralInhibition(void) : mKsize(5){}
	static LateralInhibition* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(LateralInhibition::mSingleton)  
				delete LateralInhibition::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void lateralInhibition(unsigned char* image, int height, int width, int Ksize);
	int mKsize;
};
