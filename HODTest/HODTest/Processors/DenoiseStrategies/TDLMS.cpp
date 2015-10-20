#include "./Processors/DenoiseStrategies/TDLMS.h"
#define PI 3.1415926535

//�ྲ̬����������.cpp�ļ�������
TDLMS*	TDLMS::mSingleton = NULL;

void TDLMS::denoise(const Mat& srcImg, Mat& desImg)
{
	unsigned char* cvtImg = mat2GrayImgPointer(srcImg, desImg);

	tdlms( cvtImg, desImg.rows, desImg.cols);
	Mat outimage(desImg.rows, desImg.cols,  CV_8UC1, cvtImg);
	desImg = outimage;
}

void TDLMS::tdlms( unsigned char* image, int height, int width )
{
	int  lLBytes = ((width * 8) + 31) / 32 * 4;
	int i, j, k1, k2, x, y;
	unsigned char* OutImage = new unsigned char[lLBytes*height];
	memcpy(OutImage, image, sizeof(unsigned char)*lLBytes*height);
	//��5��5�Ĺ̶���Ȩģ��ȥԤ�ⱳ��
	int ll = 3;
	int LL = 7;
	int N = LL*LL;
	float mu = 0.000001f; //��������
	float *Weight = new float[N];
	float temp = 1.f / float(N - 1);
	for (int k = 0; k<N; k++)
	{
		Weight[k] = temp;
	}
	//����LMSԤ��
	float p;
	float e;
	float sum;
	for (y = ll; y<height - ll; y++)
	{
		for (x = ll; x<width - ll; x++)
		{
			//1.�õ�Ԥ��ֵ
			p = 0;
			sum = 0;
			for (j = -ll; j <= ll; j++)
			{
				for (i = -ll; i <= ll; i++)
				{
					if (j == 0 && i == 0)
						continue;
					else
					{
						k1 = (y + j)*lLBytes + (x + i);
						k2 = (j + ll)*LL + (i + ll);
						p += float(Weight[k2] * image[k1]);
						sum += Weight[k2];
					}
				}
			}
			p = p / sum;
			if (p>255)
				OutImage[y*lLBytes + x] = 255;
			else
				OutImage[y*lLBytes + x] = (unsigned char)(p + 0.5);
			//2.�õ��в�
			e = float(OutImage[y*lLBytes + x]) - float(image[y*lLBytes + x]);
			//3.����Ȩֵ
			for (j = -ll; j <= ll; j++)
			{
				for (i = -ll; i <= ll; i++)
				{
					k1 = (y + j)*lLBytes + (x + i);
					k2 = (j + ll)*LL + (i + ll);
					Weight[k2] = Weight[k2] - 2 * mu*e*image[k1];
				}
			}
			//4.Ȩֵ��һ��

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
	delete[] Weight;
	delete[] OutImage;
}

