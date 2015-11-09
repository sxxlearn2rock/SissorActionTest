#include "./Processors/DenoiseStrategies/MaxMedianFilter.h"
#define PI 3.1415926535

#include <time.h>
#include <qDebug>
//�ྲ̬����������.cpp�ļ�������
MaxMedianFilter*	MaxMedianFilter::mSingleton = NULL;

void MaxMedianFilter::denoise(const Mat& srcImg, Mat& desImg)
{
//clock_t t1, t2;
//t1 = clock();
		unsigned char* cvtImg = mat2GrayImgPointer(srcImg, desImg);
//t2 = clock();
//qDebug() << (double)(t2-t1)*1000 << "us" ;


	maxmedianfilter( cvtImg, desImg.rows, desImg.cols);
//clock_t t3, t4;
//t3 = clock();
	Mat outimage(desImg.rows, desImg.cols,  CV_8UC1, cvtImg);
	desImg = outimage;
//t4 = clock();
//qDebug() << (double)(t4-t3)*1000 << "us" ;

}

void MaxMedianFilter::maxmedianfilter( unsigned char* image, int height, int width )
{
	int  lLBytes = ((width * 8) + 31) / 32 * 4;
	int i, j, k, k1, k2, x, y;
	unsigned char* OutImage = new unsigned char[lLBytes*height];
	memcpy(OutImage, image, sizeof(unsigned char)*lLBytes*height);
	//��7��7��ģ��
	int ll = 3;
	int LL = 7;
	unsigned char sum[4];
	unsigned char max;
	unsigned char Median[7];
	// ���������ֵ�˲� (��Ե������)
	for (y = ll; y<height - ll; y++)
	{
		for (x = ll; x<width - ll; x++)
		{
			//1.ˮƽ����ֵ
			for (k = -ll; k <= ll; k++)
			{
				k1 = k + ll;
				k2 = y*lLBytes + (x + k);
				Median[k1] = image[k2];
			}
			for (j = 0; j<LL; j++)
			{
				k1 = Median[j];
				k2 = j;
				for (i = j + 1; i<LL; i++)
				{
					if (k1>Median[i])
					{
						k1 = Median[i];
						k2 = i;
					}
				}
				Median[k2] = Median[j];
				Median[j] = k1;
			}
			sum[0] = Median[3];
			//2.��ֱ����ֵ
			for (k = -ll; k <= ll; k++)
			{
				k1 = k + ll;
				k2 = (y + k)*lLBytes + x;
				Median[k1] = image[k2];
			}
			for (j = 0; j<LL; j++)
			{
				k1 = Median[j];
				k2 = j;
				for (i = j + 1; i<LL; i++)
				{
					if (k1>Median[i])
					{
						k1 = Median[i];
						k2 = i;
					}
				}
				Median[k2] = Median[j];
				Median[j] = k1;
			}
			sum[1] = Median[3];
			//3.45������ֵ
			for (k = -ll; k <= ll; k++)
			{
				k1 = k + ll;
				k2 = (y - k)*lLBytes + (x + k);
				Median[k1] = image[k2];
			}
			for (j = 0; j<LL; j++)
			{
				k1 = Median[j];
				k2 = j;
				for (i = j + 1; i<LL; i++)
				{
					if (k1>Median[i])
					{
						k1 = Median[i];
						k2 = i;
					}
				}
				Median[k2] = Median[j];
				Median[j] = k1;
			}
			sum[2] = Median[3];
			//4.135������ֵ
			for (k = -ll; k <= ll; k++)
			{
				k1 = k + ll;
				k2 = (y + k)*lLBytes + (x + k);
				Median[k1] = image[k2];
			}
			for (j = 0; j<LL; j++)
			{
				k1 = Median[j];
				k2 = j;
				for (i = j + 1; i<LL; i++)
				{
					if (k1>Median[i])
					{
						k1 = Median[i];
						k2 = i;
					}
				}
				Median[k2] = Median[j];
				Median[j] = k1;
			}
			sum[3] = Median[3];

			//�����ֵ
			max = 0;
			for (int k = 0; k<4; k++)
			{
				if (sum[k]>max)
					max = sum[k];
			}
			if (max>255)
				OutImage[y*lLBytes + x] = 255;
			else
				OutImage[y*lLBytes + x] = (unsigned char)(max + 0.5);
		}
	}
	//	memcpy(image,OutImage,sizeof(unsigned char)*lLBytes*height);
	//ԭͼ�뱳���������һ��
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			float temp1;                                   //��ͼ
			//			temp1 = float(image[lLBytes*y + x] - OutImage[lLBytes*y + x]);  //��ԭʼͼ���ȥ����ͼ��
			temp1 = float( OutImage[lLBytes*y + x] );
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