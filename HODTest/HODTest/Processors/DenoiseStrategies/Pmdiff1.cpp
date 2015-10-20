#include "./Processors/DenoiseStrategies/Pmdiff1.h"
#define PI 3.1415926535

//�ྲ̬����������.cpp�ļ�������
Pmdiff1*	Pmdiff1::mSingleton = NULL;

void Pmdiff1::denoise(const Mat& srcImg, Mat& desImg)
{
	unsigned char* cvtImg = mat2GrayImgPointer(srcImg, desImg);

	pmdiff1( cvtImg, desImg.rows, desImg.cols);
	Mat outimage(desImg.rows, desImg.cols,  CV_8UC1, cvtImg);
	desImg = outimage;
}

void Pmdiff1::pmdiff1( unsigned char* image, int height, int width )
{
	int i, x, y;                      //ѭ������
	int kappa = 30;					//�ݶ���ֵ
	int temp_kappa = kappa*kappa;
	int Num = 15;                     //ѭ������
	double lamba = 0.25;
	int option = 1;                   //�����ֹ�ʽ��option����ѡ��1����2
	int     lLBytes = ((width * 8) + 31) / 32 * 4;    //ͼ����п���֤Ϊ4�ı���

	//������ʱ�ڴ����������
	float *Dff1 = new float[(lLBytes + 2)*(height + 2)];       //�����ӱߴ�����м仺��ͼ��
	float *Pimgsource = new float[lLBytes*height];         //�洢ÿ��ѭ������Ľ��
	memset(Dff1, 0, (lLBytes + 2)*(height + 2)*sizeof(float));
	memset(Pimgsource, 0, lLBytes*height*sizeof(float));

	//�Ե�һ��ѭ����ͼ����и���ֵ
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
			Pimgsource[lLBytes*y + x] = image[lLBytes*y + x];
	}

	//ѡ��ʽһ                                    //                      1
	if (option == 1)                                 //   g(delta(*))=-------------------------------
	{                                              //                 1  +  (delta(*)/kappa)^2
		for (i = 0; i<Num; i++) //ѭ������										
		{
			//�Ի���ͼ���м丳ֵ
			for (y = 1; y <= height; y++)
			{
				for (x = 1; x <= width; x++)
					Dff1[(lLBytes + 2)*y + x] = Pimgsource[lLBytes*(y - 1) + x - 1];
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
	}
	//ѡ��ʽ��                                   //                            (delta(*))^2
	if (option == 2)                                 //   g(delta(*))=exp (-   -----------------------  )
	{                                              //                              (kappa)^2
		for (i = 0; i<Num; i++) //ѭ������														
		{	//�Ի���ͼ���м丳ֵ
			for (y = 1; y <= height; y++)
			{
				for (x = 1; x <= width; x++)
					Dff1[(lLBytes + 2)*y + x] = Pimgsource[lLBytes*(y - 1) + x - 1];
			}

			for (y = 0; y<height; y++)
			{
				for (x = 0; x<width; x++)
				{
					int       k = lLBytes*y + x;
					float temp = Pimgsource[k];
					float DN, DS, DE, DW;
					DS = Dff1[(lLBytes + 2)*y + x + 1] - temp;
					DN = Dff1[(lLBytes + 2)*(y + 2) + x + 1] - temp;
					DE = Dff1[(lLBytes + 2)*(y + 1) + x + 2] - temp;
					DW = Dff1[(lLBytes + 2)*(y + 1) + x] - temp;

					float CN, CS, CE, CW;
					//��CN.......��ֵ				
					CN = (float)(1.0 / (1 + exp(-(DN*DN / temp_kappa))));
					CS = (float)(1.0 / (1 + exp(-(DS*DS / temp_kappa))));
					CE = (float)(1.0 / (1 + exp(-(DE*DE / temp_kappa))));
					CW = (float)(1.0 / (1 + exp(-(DW*DW / temp_kappa))));
					//���ս��
					temp = (float)(temp + lamba*(CN*DN +
						CS*DS +
						CE*DE +
						CW*DW));
					Pimgsource[k] = temp;
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
			Pimgsource[lLBytes*y + x] = (unsigned char)temp1;
		}
	}

	float maxT = 1.0;
	//�Խ��ͼ����й�һ����������ʾ�ĶԱȶ�
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			if (Pimgsource[lLBytes*y + x]>maxT)
				maxT = Pimgsource[lLBytes*y + x];       // ����ͼ����������ֵ
		}
	}

	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			image[lLBytes*y + x] = (unsigned char)(Pimgsource[lLBytes*y + x] * 255 / maxT);//�Բ�ֵͼ����й�һ��
		}
	}
	delete[]Dff1;
	delete[]Pimgsource;
}

