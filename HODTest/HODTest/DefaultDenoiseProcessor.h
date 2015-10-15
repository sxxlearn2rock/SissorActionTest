#pragma once
#include "DenoiseProcessor.h"

class DefaultDenosieProcessor : public DenoiseProcessor
{
public:

	~DefaultDenosieProcessor(void) {}

	static DefaultDenosieProcessor* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DefaultDenosieProcessor();
		}
		return mSingleton;
	}

	void denoise(const Mat& srcImg, Mat& desImg);
private:
		DefaultDenosieProcessor(void) {}
		static DefaultDenosieProcessor* mSingleton;

		class CGarbo   //该私有内嵌类的唯一工作就是在析构函数中删除单例
		{  
		public:  
			~CGarbo()  
			{  
				if(DefaultDenosieProcessor::mSingleton)  
					delete DefaultDenosieProcessor::mSingleton;  
			}  
		};  
		static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  
};
