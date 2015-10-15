#pragma once
#include "DenoiseStrategy.h"

//单例模式
class DefaultDenosieStrategy : public DenoiseStrategy
{
public:

	~DefaultDenosieStrategy(void) {}

	static DefaultDenosieStrategy* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DefaultDenosieStrategy();
		}
		return mSingleton;
	}

	void setArg1(int arg) { mArg1 = arg; }

	void denoise(const Mat& srcImg, Mat& desImg);
private:
		DefaultDenosieStrategy(void) : mArg1(5) {}
		static DefaultDenosieStrategy* mSingleton;

		class CGarbo   //该私有内嵌类的唯一工作就是在析构函数中删除单例
		{  
		public:  
			~CGarbo()  
			{  
				if(DefaultDenosieStrategy::mSingleton)  
					delete DefaultDenosieStrategy::mSingleton;  
			}  
		};  
		static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

		int mArg1;
};
