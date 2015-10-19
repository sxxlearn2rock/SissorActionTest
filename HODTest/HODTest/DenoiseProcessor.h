#pragma once
#include "./Processors/strategies.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//单例模式
class DenoiseProcessor
{
public:
	~DenoiseProcessor(void) {}

	static DenoiseProcessor* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DenoiseProcessor;
		}
		return mSingleton;
	}

	void setDenoiseStrategy(DenoiseStrategy* denoiseStrategy) { mDenoiseStrategy = denoiseStrategy; }

	void process(Mat& inputImg, Mat& outputImg);
private:
	DenoiseProcessor(void) {}
	DenoiseProcessor(DenoiseStrategy* denoiseStrategy) { mDenoiseStrategy = denoiseStrategy; }

	class Cleaner   //该私有内嵌类的唯一工作就是在析构函数中删除单例
	{  
	public:  
		~Cleaner()  
		{  
			if(DenoiseProcessor::mSingleton)  
				delete DenoiseProcessor::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  

	static DenoiseProcessor* mSingleton;
	DenoiseStrategy* mDenoiseStrategy;
};

