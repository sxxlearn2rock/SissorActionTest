#include "./Processors/DenoiseStrategies/Pmdiffmy.h"
#define PI 3.1415926535

//类静态变量必须在.cpp文件里声明
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
	int kappa = 30;                   //梯度阈值
	int temp_kappa = kappa*kappa;

	int Num = 6;                      //循环次数,经过改进后，对于小目标，这个地方可以循环次数少一些。大目标，循环次数可以增加一些。
	double lamba = 0.25;
	int  lLBytes = ((width * 8) + 31) / 32 * 4;
	//申请零时内存存贮各数据
	float *Dff1 = new float[(lLBytes + 2)*(height + 2)];       //经过加边处理的中间缓冲图像
	float *Pimgsource = new float[lLBytes*height];         //存储每次循环处理的结果
	memset(Dff1, 0, (lLBytes + 2)*(height + 2)*sizeof(float));
	memset(Pimgsource, 0, lLBytes*height*sizeof(float));

	//计算平均3*3领域灰度图（均值滤波后的图像）
	unsigned char * MeanImage = new unsigned char[lLBytes*height];
	memcpy(MeanImage, image, sizeof(unsigned char)*lLBytes*height);      //为了处理边缘点
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

	//初始循环图像赋初值；
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			int k = lLBytes*y + x;
			Pimgsource[k] = MeanImage[k];
		}
	}

	for (i = 0; i<Num; i++)               //循环次数
	{	//对缓冲图像中间赋值
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
				float DN, DS, DE, DW;                   //计算各个方向的梯度
				DS = Dff1[(lLBytes + 2)*y + x + 1] - temp;
				DN = Dff1[(lLBytes + 2)*(y + 2) + x + 1] - temp;
				DE = Dff1[(lLBytes + 2)*(y + 1) + x + 2] - temp;
				DW = Dff1[(lLBytes + 2)*(y + 1) + x] - temp;

				float CN, CS, CE, CW;
				//对CN.......赋值				
				CN = (float)exp(-(DN*DN / temp_kappa));
				CS = (float)exp(-(DS*DS / temp_kappa));
				CE = (float)exp(-(DE*DE / temp_kappa));
				CW = (float)exp(-(DW*DW / temp_kappa));
				//最终结果
				temp = (float)(temp + lamba*(CN*DN +
					CS*DS +
					CE*DE +
					CW*DW));
				Pimgsource[k] = temp;
			}
		}
	}

	//以上得到的是背景建模（经过各向异性扩散过滤）后的图像；
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
	//原图与背景做差，并归一化
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			float temp1;                                   //差图
			temp1 = float(image[lLBytes*y + x] - Pimgsource[lLBytes*y + x]);  //用原始图像减去背景图像
			if (temp1<0.0)
				temp1 = 0;
			if (temp1>255.0)
				temp1 = 255.0;
			image[lLBytes*y + x] = (unsigned char)temp1;
		}
	}

	float maxT = 1.0;
	//对结果图像进行归一化，扩大显示的对比度
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			if (image[lLBytes*y + x]>maxT)
				maxT = image[lLBytes*y + x];       // 计算图像的最高像素值
		}
	}

	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			image[lLBytes*y + x] = (unsigned char)(image[lLBytes*y + x] * 255 / maxT);//对差值图像进行归一化
		}
	}
	delete[]Dff1;
	delete[]Pimgsource;
	delete[]MeanImage;
}

