#include "./Processors/SegmentStrategies/Ksw2dSegment.h"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#define LINEBYTES(bits)  (((bits) + 31) / 32 * 4) 
using cv::Mat;

Ksw2dSegment* Ksw2dSegment::mSingleton = NULL;

void Ksw2dSegment::process( Mat& srcImg, Mat& segImg, Mat& desImg, vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects )
{
	int width = srcImg.cols * srcImg.channels();
	int height = srcImg.rows;

	//Mat类转化成数组指针
	unsigned char* convertImage=new unsigned char [width*height]; // 创建一个一维图像，作为实验室已有算法的输入
	unsigned char* p;                                             // 遍历读取mat类中每一个像素值
	int i , j;
	for (i = 0; i < height; i++)
	{
		p = srcImg.ptr<unsigned char>(i);                     // 该指针指向mat类中矩阵的每行行首
		for (j = 0; j < width; j++)
		{
			convertImage[i*width+j]=p[j];                         // 将mat类中的矩阵转换成一个一维图像
		}
	}

	ksw2dSegmentation(convertImage, width, height);               // 函数调用	
	Mat segImgTemp(height, width, CV_8UC1, convertImage);        // 一维图像数组转化为Mat类
	segImg = segImgTemp;
	morphFilter(segImg, desImg, mErosionType, mDilationType, mErosionSize, mDilationSize);
	positionResult(desImg, desImg, coordinates, rotatedRects);
}

void Ksw2dSegment::ksw2dSegmentation( unsigned char* image,int width,int height )
{
	//1.计算图像的二维直方图
	//////////////////////////////////////////////////////
	int *histArray_2D = new int [256*256];
	//计算平均3*3邻域灰度图（均值滤波后的图像）
	int lLBytes = LINEBYTES(width * 8);//对于宽度不是4的倍数的图片，改成4的倍数
	int i, j, x, y;
	unsigned char * meanImage = new unsigned char [lLBytes * height];
	memcpy ( meanImage, image, sizeof(unsigned char) * lLBytes * height );//为了处理边缘点
	float mean;
	for(y = 1; y < height - 1; y++)
	{
		for(x = 1; x < width - 1; x++)
		{
			mean = 0.0;
			for(j = -1; j <= 1; j++)
			{
				for(i = -1; i <= 1; i++)
				{
					mean += image[(y + j) * lLBytes + x + i];
				}
			}
			mean  /= (float)(3 * 3); //3*3邻域的平均值
			meanImage[y * lLBytes + x] = (unsigned char)(mean + 0.5); //考虑边缘点
		}
	}
	
	//直方图数组清0
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			histArray_2D[j * 256 + i] = 0;//二维直方图初始为256*256，默认处理8位灰度图
		}
	}
	//中间变量 
	int temp1, temp2;
	for (y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			int k = lLBytes * y + x;
			temp1 = image[k];//取原图灰度
			temp2 = meanImage[k];//取均值图灰度，与temp1组成二维向量
			histArray_2D[temp1 * 256 + temp2] = histArray_2D[temp1 * 256 + temp2] + 1;//灰度为（temp1,temp2）元素个数
		}
	}

	//2.求取最佳阈值(非常耗时)
	/////////////////////////////////////////////////////////////////
	float *P_xy = new float [256 * 256];    //二维直方图的联合概率密度
	float N = float(width * height);
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			P_xy[j * 256+i]  = float(histArray_2D[j * 256 + i]) / N;
		}
	}
	float Hl2D = 0.0, Pa = 0.0, Ha = 0;
	//计算Hl2D
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			if (P_xy[j * 256 + i] < 0.0000000000001)//概率密度为零时不计算熵值
				continue;
			Hl2D += -P_xy[j * 256 + i] * float( log10(P_xy[j * 256 + i]) );//整个图像的熵
		}
	}
	//循环求取最佳阈值
	//熵及最大熵
	float Entropy, maxEntropy = 0;
	int Max_y = 0,Max_x = 0;
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			Pa += P_xy[j * 256 + i];//背景概率
			if (P_xy[j * 256 + i] < 0.0000000000001)
				continue;
			Ha += -P_xy[j * 256 + i] * float( log10(P_xy[j * 256 + i]) );
			Entropy = float(log10(Pa * (1 - Pa)) + Ha / Pa + (Hl2D - Ha) / (1 - Pa));//总体熵
			if (Entropy > maxEntropy)
			{
				maxEntropy = Entropy;//取得最大熵
				Max_x = i;//阈值更新
				Max_y = j;
			}
		}
	}

	//3.阈值分割
	//////////////////////////////////////////////////
	for (j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			if (image[j * lLBytes + i] >= Max_y && meanImage[j * lLBytes+i] >= Max_x)//实际灰度值大于阈值并且平均灰度值大于阈值时视为目标
			{
				image[j * lLBytes + i] = 255;//目标
			}
			else
			{
				image[j * lLBytes + i] = 0;//背景
			}
		}
	}
	
	/*  waited to improvement 
	delete [] histArray_2D;
	delete [] P_xy;
	*/
}
