#include "./Processors/DenoiseStrategies/DefaultDenoiseStrategy.h"

//类静态变量必须在.cpp文件里声明
DefaultDenosieStrategy*	DefaultDenosieStrategy::mSingleton = NULL;

void DefaultDenosieStrategy::denoise(const Mat& srcImg, Mat& desImg)
{
	desImg = srcImg;
}



