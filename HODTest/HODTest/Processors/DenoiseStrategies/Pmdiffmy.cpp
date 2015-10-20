#include "./Processors/DenoiseStrategies/Pmdiffmy.h"
#define PI 3.1415926535

//�ྲ̬����������.cpp�ļ�������
Pmdiffmy*	Pmdiffmy::mSingleton = NULL;

void Pmdiffmy::denoise(const Mat& srcImg, Mat& desImg)
{
	unsigned char* cvtImg = mat2GrayImgPointer(srcImg, desImg);

	pmdiffmy( cvtImg, desImg.rows, desImg.cols);
	Mat outimage(desImg.rows, desImg.cols,  CV_8UC1, cvtImg);
	desImg = outimage;
}

void Pmdiffmy::pmdiffmy( unsigned char* image, int height, int width )
{
	int i, j, x, y;
	int kappa = 30;                   //�ݶ���ֵ
	int temp_kappa = kappa*kappa;

	int Num = 6;                      //ѭ������,�����Ľ��󣬶���СĿ�꣬����ط�����ѭ��������һЩ����Ŀ�꣬ѭ��������������һЩ��
	double lamba = 0.25;
	int  lLBytes = ((width * 8) + 31) / 32 * 4;
	//������ʱ�ڴ����������
	float *Dff1 = new float[(lLBytes + 2)*(height + 2)];       //�����ӱߴ�����м仺��ͼ��
	float *Pimgsource = new float[lLBytes*height];         //�洢ÿ��ѭ������Ľ��
	memset(Dff1, 0, (lLBytes + 2)*(height + 2)*sizeof(float));
	memset(Pimgsource, 0, lLBytes*height*sizeof(float));

	//����ƽ��3*3����Ҷ�ͼ����ֵ�˲����ͼ��
	unsigned char * MeanImage = new unsigned char[lLBytes*height];
	memcpy(MeanImage, image, sizeof(unsigned char)*lLBytes*height);      //Ϊ�˴����Ե��
	float mean;
	for (y = 1; y<height - 1; y++)
	{
		for (x = 1; x<width - 1; x++)
		{
			mean = 0.0;
			for (j = -1; j <= 1; j++)
			{
				for (i = -1; i <= 1; i++)
				{
					mean += image[(y + j)*lLBytes + x + i];
				}
			}
			mean /= (float)(3 * 3);
			MeanImage[y*lLBytes + x] = (unsigned char)(mean + 0.5);
		}
	}

	//��ʼѭ��ͼ�񸳳�ֵ��
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			int k = lLBytes*y + x;
			Pimgsource[k] = MeanImage[k];
		}
	}

	for (i = 0; i<Num; i++)               //ѭ������
	{	//�Ի���ͼ���м丳ֵ
		for (y = 1; y <= height; y++)
		{
			for (x = 1; x <= width; x++)
			{
				Dff1[(lLBytes + 2)*y + x] = Pimgsource[lLBytes*(y - 1) + x - 1];
			}
		}

		for (y = 0; y<height; y++)
		{
			for (x = 0; x<width; x++)
			{
				int       k = lLBytes*y + x;
				float temp = Pimgsource[k];
				float DN, DS, DE, DW;                   //�������������ݶ�
				DS = Dff1[(lLBytes + 2)*y + x + 1] - temp;
				DN = Dff1[(lLBytes + 2)*(y + 2) + x + 1] - temp;
				DE = Dff1[(lLBytes + 2)*(y + 1) + x + 2] - temp;
				DW = Dff1[(lLBytes + 2)*(y + 1) + x] - temp;

				float CN, CS, CE, CW;
				//��CN.......��ֵ				
				CN = (float)exp(-(DN*DN / temp_kappa));
				CS = (float)exp(-(DS*DS / temp_kappa));
				CE = (float)exp(-(DE*DE / temp_kappa));
				CW = (float)exp(-(DW*DW / temp_kappa));
				//���ս��
				temp = (float)(temp + lamba*(CN*DN +
					CS*DS +
					CE*DE +
					CW*DW));
				Pimgsource[k] = temp;
			}
		}
	}

	//���ϵõ����Ǳ�����ģ����������������ɢ���ˣ����ͼ��
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			int k = lLBytes*y + x;
			if (Pimgsource[k]>255)
				Pimgsource[k] = 255;
			else
				Pimgsource[k] = (unsigned char)(Pimgsource[k] + 0.5);
		}
	}
	//ԭͼ�뱳���������һ��
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			float temp1;                                   //��ͼ
			temp1 = float(image[lLBytes*y + x] - Pimgsource[lLBytes*y + x]);  //��ԭʼͼ���ȥ����ͼ��
			if (temp1<0.0)
				temp1 = 0;
			if (temp1>255.0)
				temp1 = 255.0;
			image[lLBytes*y + x] = (unsigned char)temp1;
		}
	}

	float maxT = 1.0;
	//�Խ��ͼ����й�һ����������ʾ�ĶԱȶ�
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			if (image[lLBytes*y + x]>maxT)
				maxT = image[lLBytes*y + x];       // ����ͼ����������ֵ
		}
	}

	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			image[lLBytes*y + x] = (unsigned char)(image[lLBytes*y + x] * 255 / maxT);//�Բ�ֵͼ����й�һ��
		}
	}
	delete[]Dff1;
	delete[]Pimgsource;
	delete[]MeanImage;
}

