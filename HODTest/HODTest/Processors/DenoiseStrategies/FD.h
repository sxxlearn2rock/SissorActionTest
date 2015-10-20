#pragma once
#include "./Processors/DenoiseStrategy.h"

//分形算法
class FD : public DenoiseStrategy
{
public:

	~FD(void) {}

	static FD* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new FD();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	FD(void) {}
	static FD* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(FD::mSingleton)  
				delete FD::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void fd(unsigned char* image, int height, int width);
};
