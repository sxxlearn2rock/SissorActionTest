#include "DenoiseProcessors.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

void DefaultDenosieProcessor::denoise(const Mat& srcImg, Mat& desImg)
{
	cv::Mat ele(5,5,CV_8U,cv::Scalar(1));
	cv::morphologyEx(srcImg, desImg, cv::MORPH_CLOSE, ele);

//		cv::erode(srcImg, desImg, cv::Mat());

//		cv::Canny(srcImg, desImg, 125, 350);
}
