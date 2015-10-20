#pragma once
#include "./Processors/DenoiseStrategy.h"

//固定权值背景预测
class BaseWeightBGP : public DenoiseStrategy
{
public:

	~BaseWeightBGP(void) {}

	static BaseWeightBGP* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new BaseWeightBGP();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	BaseWeightBGP(void) {}
	static BaseWeightBGP* mSingleton;

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(BaseWeightBGP::mSingleton)  
				delete BaseWeightBGP::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	void baseweightbgp(unsigned char* image, int height, int width);
};
