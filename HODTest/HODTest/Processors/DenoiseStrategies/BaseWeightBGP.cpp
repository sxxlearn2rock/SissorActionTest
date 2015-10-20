#include "./Processors/DenoiseStrategies/BaseWeightBGP.h"
#define PI 3.1415926535

//�ྲ̬����������.cpp�ļ�������
BaseWeightBGP*	BaseWeightBGP::mSingleton = NULL;

void BaseWeightBGP::denoise(const Mat& srcImg, Mat& desImg)
{
	unsigned char* cvtImg = mat2GrayImgPointer(srcImg, desImg);

	baseweightbgp( cvtImg, desImg.rows, desImg.cols);
	Mat outimage(desImg.rows, desImg.cols,  CV_8UC1, cvtImg);
	desImg = outimage;
}

void BaseWeightBGP::baseweightbgp( unsigned char* image, int height, int width )
{
	int  lLBytes = ((width * 8) + 31) / 32 * 4;
	int i, j, k1, k2, x, y;
	unsigned char* OutImage = new unsigned char[lLBytes*height];
	memcpy(OutImage, image, sizeof(unsigned char)*lLBytes*height);
	//��7��7�Ĺ̶���Ȩģ��ȥԤ�ⱳ��
	int ll = 3;
	int LL = 7;
	float Weight[49] =
	{
		9, 9, 9, 9, 9, 9, 9,
		9, 4, 4, 4, 4, 4, 9,
		9, 4, 1, 1, 1, 4, 9,
		9, 4, 1, 0, 1, 4, 9,
		9, 4, 1, 1, 1, 4, 9,
		9, 4, 4, 4, 4, 4, 9,
		9, 9, 9, 9, 9, 9, 9
	};
	float sum;
	// ���о�� (��Ե������)
	for (y = ll; y<height - ll; y++)
	{
		for (x = ll; x<width - ll; x++)
		{
			sum = 0;
			for (j = -ll; j <= ll; j++)
			{
				for (i = -ll; i <= ll; i++)
				{
					k1 = (y + j)*lLBytes + (x + i);
					k2 = (j + ll)*LL + (i + ll);
					sum += float(Weight[k2] * image[k1]);
				}
			}
			sum /= 288;
			if (sum>255)
				OutImage[y*lLBytes + x] = 255;
			else
				OutImage[y*lLBytes + x] = (unsigned char)(sum + 0.5);
		}
	}
	//	memcpy(image,OutImage,sizeof(unsigned char)*lLBytes*height);
	//ԭͼ�뱳���������һ��
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			float temp1;                                   //��ͼ
			temp1 = float(image[lLBytes*y + x] - OutImage[lLBytes*y + x]);  //��ԭʼͼ���ȥ����ͼ��
			if (temp1<0.0)
				temp1 = 0;
			if (temp1>255.0)
				temp1 = 255.0;
			OutImage[lLBytes*y + x] = (unsigned char)temp1;
		}
	}

	float maxT = 1.0;
	//�Խ��ͼ����й�һ����������ʾ�ĶԱȶ�
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			if (OutImage[lLBytes*y + x]>maxT)
				maxT = OutImage[lLBytes*y + x];       // ����ͼ����������ֵ
		}
	}

	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			image[lLBytes*y + x] = (unsigned char)(OutImage[lLBytes*y + x] * 255 / maxT);//�Բ�ֵͼ����й�һ��
		}
	}
	delete[] OutImage;
}

