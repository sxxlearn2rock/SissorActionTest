#include "./Processors/DenoiseStrategies/DoublehistEqual.h"
#include "math.h"
#include "string.h"

//�ྲ̬����������.cpp�ļ�������
DoublehistEqual*	DoublehistEqual::mSingleton = NULL;

void DoublehistEqual::denoise(const Mat& srcImg, Mat& desImg)
{
	unsigned char* cvtImg =  mat2GrayImgPointer(srcImg, desImg);

	histEqual2( cvtImg, desImg.rows, desImg.cols);
	Mat outimage(desImg.rows, desImg.cols,  CV_8UC1, cvtImg);
	desImg = outimage;
}

void DoublehistEqual::histEqual2( unsigned char *image, int height, int width )
{
	//��ʼ��������
	double lamba = 0.25;
	int  num = 6;							//ѭ��������Խ�߼��Ч��Խ�ã����Ǹ���ʱ�� 
	int  option = 1;						//�ȴ������̵�ѡ��
	int  kappa = 30 * 30;						//�ݶ���ֵ�ϵ�ƽ��
	int  lLBytes = ((width * 8) + 31) / 32 * 4;		//��֤ͼ�����Ϊ4�ı���

	//��Ӱ˸�������˲�ģ��
	int	hN[9] = { 0, 1, 0, 0, -1, 0, 0, 0, 0 };
	int	hS[9] = { 0, 0, 0, 0, -1, 0, 0, 1, 0 };
	int	hE[9] = { 0, 0, 0, 0, -1, 1, 0, 0, 0 };
	int	hW[9] = { 0, 0, 0, 1, -1, 0, 0, 0, 0 };
	int	hNE[9] = { 0, 0, 1, 0, -1, 0, 0, 0, 0 };
	int	hSE[9] = { 0, 0, 0, 0, -1, 0, 0, 0, 1 };
	int	hSW[9] = { 0, 0, 0, 0, -1, 0, 1, 0, 0 };
	int hNW[9] = { 1, 0, 0, 0, -1, 0, 0, 0, 0 };


	//�����ڴ�洢���������˲���Ľ��
	float *deltaN = new float[lLBytes*height];
	memset(deltaN, 0, lLBytes*height*sizeof(float));
	float *deltaS = new float[lLBytes*height];
	memset(deltaS, 0, lLBytes*height*sizeof(float));
	float *deltaW = new float[lLBytes*height];
	memset(deltaW, 0, lLBytes*height*sizeof(float));
	float *deltaE = new float[lLBytes*height];
	memset(deltaE, 0, lLBytes*height*sizeof(float));
	float *deltaNE = new float[lLBytes*height];
	memset(deltaNE, 0, lLBytes*height*sizeof(float));
	float *deltaSE = new float[lLBytes*height];
	memset(deltaSE, 0, lLBytes*height*sizeof(float));
	float *deltaSW = new float[lLBytes*height];
	memset(deltaSW, 0, lLBytes*height*sizeof(float));
	float *deltaNW = new float[lLBytes*height];
	memset(deltaNW, 0, lLBytes*height*sizeof(float));

	//�����ڴ�洢�м�ͼ����
	float *pimgsorce = new float[lLBytes*height];
	memset(pimgsorce, 0, lLBytes*height*sizeof(float));

	int x, y;			//ѭ������
	//��pimgsorce����ֵ
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			pimgsorce[lLBytes*y + x] = image[lLBytes*y + x];
		}
	}
	//ѭ����ʼ
	for (int i = 1; i<num; i++)
	{
		imfilter((float *)pimgsorce, (float *)deltaN, width, height, hN);
		imfilter((float *)pimgsorce, (float *)deltaS, width, height, hS);
		imfilter((float *)pimgsorce, (float *)deltaW, width, height, hW);
		imfilter((float *)pimgsorce, (float *)deltaE, width, height, hE);
		imfilter((float *)pimgsorce, (float *)deltaNE, width, height, hNE);
		imfilter((float *)pimgsorce, (float *)deltaSE, width, height, hSE);
		imfilter((float *)pimgsorce, (float *)deltaSW, width, height, hSW);
		imfilter((float *)pimgsorce, (float *)deltaNW, width, height, hNW);

		//ѡ��ʽһ                                    //                      1
		if (option == 1)                                 //   g(delta(*))=-------------------------------
		{                                              //                 1  +  (delta(*)/kappa)^2
			for (y = 0; y<height; y++)
			{
				for (x = 0; x<width; x++)
				{
					int	  k = lLBytes*y + x;
					float CN, CS, CE, CW, CNE, CSE, CSW, CNW;
					CN = (float)(exp(-(deltaN[k] * deltaN[k] / kappa)));
					CS = (float)(exp(-(deltaS[k] * deltaS[k] / kappa)));
					CE = (float)(exp(-(deltaE[k] * deltaE[k] / kappa)));
					CW = (float)(exp(-(deltaW[k] * deltaW[k] / kappa)));
					CNE = (float)(exp(-(deltaNE[k] * deltaNE[k] / kappa)));
					CSE = (float)(exp(-(deltaSE[k] * deltaSE[k] / kappa)));
					CSW = (float)(exp(-(deltaSW[k] * deltaSW[k] / kappa)));
					CNW = (float)(exp(-(deltaNW[k] * deltaNW[k] / kappa)));
					pimgsorce[k] = (float)(pimgsorce[k] + lamba*(CN*deltaN[k] + CS*deltaS[k] + CW*deltaW[k] + CE*deltaE[k] +
						(CNE*deltaNE[k] + CSE*deltaSE[k] + CSW*deltaSW[k] + CNW*deltaNW[k]) / 2));
				}
			}
		}
		//ѡ��ʽ��                                   //                            (delta(*))^2
		if (option == 2)                                 //   g(delta(*))=exp (-   -----------------------  )
		{                                              //                              (kappa)^2
			for (y = 0; y<height; y++)
			{
				for (x = 0; x<width; x++)
				{
					int	  k = lLBytes*y + x;
					float CN, CS, CE, CW, CNE, CSE, CSW, CNW;
					CN = (float)(1 / (1 + exp((deltaN[k] * deltaN[k] / kappa))));
					CS = (float)(1 / (1 + exp((deltaS[k] * deltaS[k] / kappa))));
					CE = (float)(1 / (1 + exp((deltaE[k] * deltaE[k] / kappa))));
					CW = (float)(1 / (1 + exp((deltaW[k] * deltaW[k] / kappa))));
					CNE = (float)(1 / (1 + exp((deltaNE[k] * deltaNE[k] / kappa))));
					CSE = (float)(1 / (1 + exp((deltaSE[k] * deltaSE[k] / kappa))));
					CSW = (float)(1 / (1 + exp((deltaSW[k] * deltaSW[k] / kappa))));
					CNW = (float)(1 / (1 + exp((deltaNW[k] * deltaNW[k] / kappa))));

					pimgsorce[k] = (float)(pimgsorce[k] + lamba*(CN*deltaN[k] + CS*deltaS[k] + CW*deltaW[k] + CE*deltaE[k] +
						(CNE*deltaNE[k] + CSE*deltaSE[k] + CSW*deltaSW[k] + CNW*deltaNW[k]) / 2));
				}
			}
		}
	}

	//���ϵõ����Ǳ�����ģ����������������ɢ���ˣ����ͼ��
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			int k = lLBytes*y + x;
			if (pimgsorce[k]>255)
				pimgsorce[k] = 255;
			else
				pimgsorce[k] = (unsigned char)(pimgsorce[k] + 0.5);
		}
	}
	//ԭͼ�뱳���������һ��
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			float temp1;                                   //��ͼ
			temp1 = float(image[lLBytes*y + x] - pimgsorce[lLBytes*y + x]);  //��ԭʼͼ���ȥ����ͼ��
			if (temp1<0.0)
				temp1 = 0;
			if (temp1>255.0)
				temp1 = 255.0;
			pimgsorce[lLBytes*y + x] = (unsigned char)temp1;
		}
	}

	float maxT = 1.0;
	//�Խ��ͼ����й�һ����������ʾ�ĶԱȶ�
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			if (pimgsorce[lLBytes*y + x]>maxT)
				maxT = pimgsorce[lLBytes*y + x];       // ����ͼ����������ֵ
		}
	}

	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			image[lLBytes*y + x] = (unsigned char)(pimgsorce[lLBytes*y + x] * 255 / maxT);//�Բ�ֵͼ����й�һ��
		}
	}
	delete[]pimgsorce;
	delete[]deltaE;
	delete[]deltaN;
	delete[]deltaS;
	delete[]deltaW;
	delete[]deltaNE;
	delete[]deltaSE;
	delete[]deltaNW;
	delete[]deltaSW;
}

void DoublehistEqual::imfilter( float *pimgsorce, float *image1, int width, int height, int *moban )
{
	int  lLBytes = ((width * 8) + 31) / 32 * 4;				//��֤ͼ����п��ܹ���4����
	//���ȶ�ͼ�������Ե����Ե����0�������ھ������
	float *buffer = new float[(height + 2)*(lLBytes + 2)];
	memset(buffer, 0, (height + 2)*(lLBytes + 2)*sizeof(float));
	int x, y;										//ѭ������
	for (y = 1; y <= height; y++)
	{
		for (x = 1; x <= width; x++)
		{
			buffer[(lLBytes + 2)*y + x] = pimgsorce[lLBytes*(y - 1) + x - 1];  //��ͼ��������������
		}
	}

	//�������
	for (y = 1; y<height + 1; y++)
	{
		for (x = 1; x<width + 1; x++)
		{
			float temp;
			int k1 = (lLBytes + 2)*(y - 1) + x - 1;
			int k2 = (lLBytes + 2)*y + x - 1;
			int k3 = (lLBytes + 2)*(y + 1) + x - 1;
			temp = buffer[k1] * moban[6] + buffer[k1 + 1] * moban[7] +
				buffer[k1 + 2] * moban[8] + buffer[k2] * moban[3] +
				buffer[k2 + 1] * moban[4] + buffer[k2 + 2] * moban[5] +
				buffer[k3] * moban[0] + buffer[k3 + 1] * moban[1] +
				buffer[k3 + 2] * moban[2];
			image1[lLBytes*(y - 1) + x - 1] = temp;
		}
	}
	delete[] buffer;
}


