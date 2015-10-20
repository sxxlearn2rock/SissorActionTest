#pragma once
#include "./Processors/DenoiseStrategy.h"

//基于自适应权值背景预测
class TDLMS : public DenoiseStrategy
{
public:

	~TDLMS(void) {}

	static TDLMS* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new TDLMS();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	TDLMS(void) {}
	static TDLMS* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(TDLMS::mSingleton)  
				delete TDLMS::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void tdlms(unsigned char* image, int height, int width);
};
