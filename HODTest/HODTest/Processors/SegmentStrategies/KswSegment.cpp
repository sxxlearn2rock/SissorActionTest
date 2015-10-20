#include "./Processors/SegmentStrategies/KswSegment.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat;
typedef enum {back,object} entropy_state;
float total;

KswSegment* KswSegment::mSingleton = NULL;

void KswSegment::process( Mat& srcImg, Mat& segImg, Mat& desImg, vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects )
{
	Mat hist = histCalculate(srcImg).t();
	maxEntropy(srcImg, segImg, hist);
	morphFilter(segImg, desImg, mErosionType, mDilationType, mErosionSize, mDilationSize);
	positionResult(desImg, desImg, coordinates, rotatedRects);
}

//����ֱ��ͼ;
Mat  KswSegment::histCalculate(const Mat& src)
{
	Mat hist;
	int bins = 256;
	int histSize[] = {bins};
	float range[] = {0, 256};
	const float* ranges[] = {range};
	int channels[] = {0};
	calcHist(&src, 1, channels, Mat(), hist, 1, histSize, ranges, true, false);//����ԭͼ��ֱ��ͼ
	return hist;
}

//���㵱ǰ��;
float  KswSegment::calEntropy(const Mat& hist, int threshold)
{
	float total_back = 0, total_object = 0;
	float entropy_back = 0,entropy_object = 0;
	float entropy = 0;
	int i = 0;

	const float* hist_p = (float*) hist.ptr<float>(0);
	for (i = 0; i < threshold; i++)
	{
		total_back += hist_p[i];
	}
	total_object = total - total_back;

	//������;
	for (i = 0; i < threshold; i++)
	{
		if(hist_p[i] == 0)
			continue;
		float percentage = hist_p[i] / total_back;
		entropy_back += -percentage * logf(percentage); // �����Ķ��幫ʽ
	}
	//ǰ����;
	for (i = threshold; i < hist.cols; i++)
	{
		if(hist_p[i]==0)
		{
			continue;
		}
		float percentage = hist_p[i] / total_object;
		entropy_object += -percentage * logf(percentage); // �����Ķ��幫ʽ��
	}

	entropy = entropy_object + entropy_back;
	return entropy;
}

//�������أ���Ϊ��ֵ
void  KswSegment::maxEntropy(Mat srcImg, Mat& dstImg, Mat hist)
{
	total = sum(hist)[0];
	float MaxEntropyValue = 0.0, MaxEntropyThreshold=0.0;
	float tmp;
	for (int i = 0; i < hist.cols; i++)
	{
		tmp = calEntropy(hist, i);
		if(tmp > MaxEntropyValue)
		{
			MaxEntropyValue = tmp;
			MaxEntropyThreshold = i;
		}
	}
	cv::threshold(srcImg, dstImg, MaxEntropyThreshold, 255, CV_THRESH_BINARY);//��ֵ����
}


