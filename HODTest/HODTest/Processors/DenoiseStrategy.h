#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using cv::Mat;

//所有去噪策略的父类
class DenoiseStrategy
{
public:
	DenoiseStrategy(void) {}
	~DenoiseStrategy(void) {}

	virtual void denoise(const Mat& srcImg, Mat& desImg) = 0;
protected:
	unsigned char* mat2GrayImgPointer(const Mat& mat, Mat& desMat)
	{
		cv::cvtColor(mat, desMat, CV_BGR2GRAY);
		int nr = desMat.rows;
		int nc = desMat.cols;
		unsigned char* covertimage = new unsigned char[nr * nc];							     // 创建一个一维图像，作为实验室已有算法的输入
		unsigned char* p;
		int i, j;
		for (i = 0; i<nr; i++)
		{
			p = desMat.ptr<unsigned char>(i);			  // 该指针指向mat类中矩阵的每行行首
			for (j = 0; j<nc; j++)
			{
				covertimage[i*nc + j] = p[j];							  // 将mat类中的矩阵转换成一个一维图像
			}
		}
			return covertimage;
	}


};

