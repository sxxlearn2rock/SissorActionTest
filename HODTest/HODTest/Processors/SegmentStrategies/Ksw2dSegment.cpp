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

	//Mat��ת��������ָ��
	unsigned char* convertImage=new unsigned char [width*height]; // ����һ��һάͼ����Ϊʵ���������㷨������
	unsigned char* p;                                             // ������ȡmat����ÿһ������ֵ
	int i , j;
	for (i = 0; i < height; i++)
	{
		p = srcImg.ptr<unsigned char>(i);                     // ��ָ��ָ��mat���о����ÿ������
		for (j = 0; j < width; j++)
		{
			convertImage[i*width+j]=p[j];                         // ��mat���еľ���ת����һ��һάͼ��
		}
	}

	ksw2dSegmentation(convertImage, width, height);               // ��������	
	Mat segImgTemp(height, width, CV_8UC1, convertImage);        // һάͼ������ת��ΪMat��
	segImg = segImgTemp;
	morphFilter(segImg, desImg, mErosionType, mDilationType, mErosionSize, mDilationSize);
	positionResult(desImg, desImg, coordinates, rotatedRects);
}

void Ksw2dSegment::ksw2dSegmentation( unsigned char* image,int width,int height )
{
	//1.����ͼ��Ķ�άֱ��ͼ
	//////////////////////////////////////////////////////
	int *histArray_2D = new int [256*256];
	//����ƽ��3*3����Ҷ�ͼ����ֵ�˲����ͼ��
	int lLBytes = LINEBYTES(width * 8);//���ڿ�Ȳ���4�ı�����ͼƬ���ĳ�4�ı���
	int i, j, x, y;
	unsigned char * meanImage = new unsigned char [lLBytes * height];
	memcpy ( meanImage, image, sizeof(unsigned char) * lLBytes * height );//Ϊ�˴����Ե��
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
			mean  /= (float)(3 * 3); //3*3�����ƽ��ֵ
			meanImage[y * lLBytes + x] = (unsigned char)(mean + 0.5); //���Ǳ�Ե��
		}
	}
	
	//ֱ��ͼ������0
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			histArray_2D[j * 256 + i] = 0;//��άֱ��ͼ��ʼΪ256*256��Ĭ�ϴ���8λ�Ҷ�ͼ
		}
	}
	//�м���� 
	int temp1, temp2;
	for (y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			int k = lLBytes * y + x;
			temp1 = image[k];//ȡԭͼ�Ҷ�
			temp2 = meanImage[k];//ȡ��ֵͼ�Ҷȣ���temp1��ɶ�ά����
			histArray_2D[temp1 * 256 + temp2] = histArray_2D[temp1 * 256 + temp2] + 1;//�Ҷ�Ϊ��temp1,temp2��Ԫ�ظ���
		}
	}

	//2.��ȡ�����ֵ(�ǳ���ʱ)
	/////////////////////////////////////////////////////////////////
	float *P_xy = new float [256 * 256];    //��άֱ��ͼ�����ϸ����ܶ�
	float N = float(width * height);
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			P_xy[j * 256+i]  = float(histArray_2D[j * 256 + i]) / N;
		}
	}
	float Hl2D = 0.0, Pa = 0.0, Ha = 0;
	//����Hl2D
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			if (P_xy[j * 256 + i] < 0.0000000000001)//�����ܶ�Ϊ��ʱ��������ֵ
				continue;
			Hl2D += -P_xy[j * 256 + i] * float( log10(P_xy[j * 256 + i]) );//����ͼ�����
		}
	}
	//ѭ����ȡ�����ֵ
	//�ؼ������
	float Entropy, maxEntropy = 0;
	int Max_y = 0,Max_x = 0;
	for (j = 0; j < 256; j++)
	{
		for(i = 0; i < 256; i++)
		{
			Pa += P_xy[j * 256 + i];//��������
			if (P_xy[j * 256 + i] < 0.0000000000001)
				continue;
			Ha += -P_xy[j * 256 + i] * float( log10(P_xy[j * 256 + i]) );
			Entropy = float(log10(Pa * (1 - Pa)) + Ha / Pa + (Hl2D - Ha) / (1 - Pa));//������
			if (Entropy > maxEntropy)
			{
				maxEntropy = Entropy;//ȡ�������
				Max_x = i;//��ֵ����
				Max_y = j;
			}
		}
	}

	//3.��ֵ�ָ�
	//////////////////////////////////////////////////
	for (j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			if (image[j * lLBytes + i] >= Max_y && meanImage[j * lLBytes+i] >= Max_x)//ʵ�ʻҶ�ֵ������ֵ����ƽ���Ҷ�ֵ������ֵʱ��ΪĿ��
			{
				image[j * lLBytes + i] = 255;//Ŀ��
			}
			else
			{
				image[j * lLBytes + i] = 0;//����
			}
		}
	}
	
	/*  waited to improvement 
	delete [] histArray_2D;
	delete [] P_xy;
	*/
}
