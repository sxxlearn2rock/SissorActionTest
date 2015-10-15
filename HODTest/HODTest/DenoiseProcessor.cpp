#include "DenoiseProcessor.h"

DenoiseProcessor* DenoiseProcessor::mSingleton = NULL;

void DenoiseProcessor::process(Mat& inputImg, Mat& outputImg)
{
	mDenoiseStrategy->denoise(inputImg, outputImg);
}
