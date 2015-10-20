#pragma once
#include "./Processors/DenoiseStrategy.h"

//分块区域最大化背景抑制
class LMPM : public DenoiseStrategy
{
public:

	~LMPM(void) {}

	static LMPM* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new LMPM();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	LMPM(void) {}
	static LMPM* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(LMPM::mSingleton)  
				delete LMPM::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void lmpm(unsigned char* image, int height, int width);
};
