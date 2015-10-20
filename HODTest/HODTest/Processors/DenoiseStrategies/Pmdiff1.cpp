#include "./Processors/DenoiseStrategies/Pmdiff1.h"
#define PI 3.1415926535

//类静态变量必须在.cpp文件里声明
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
	int i, x, y;                      //循环变量
	int kappa = 30;					//梯度阈值
	int temp_kappa = kappa*kappa;
	int Num = 15;                     //循环次数
	double lamba = 0.25;
	int option = 1;                   //有两种公式，option可以选择1或者2
	int     lLBytes = ((width * 8) + 31) / 32 * 4;    //图像的列宽，保证为4的倍数

	//申请零时内存存贮各数据
	float *Dff1 = new float[(lLBytes + 2)*(height + 2)];       //经过加边处理的中间缓冲图像
	float *Pimgsource = new float[lLBytes*height];         //存储每次循环处理的结果
	memset(Dff1, 0, (lLBytes + 2)*(height + 2)*sizeof(float));
	memset(Pimgsource, 0, lLBytes*height*sizeof(float));

	//对第一次循环的图像进行赋初值
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
			Pimgsource[lLBytes*y + x] = image[lLBytes*y + x];
	}

	//选择公式一                                    //                      1
	if (option == 1)                                 //   g(delta(*))=-------------------------------
	{                                              //                 1  +  (delta(*)/kappa)^2
		for (i = 0; i<Num; i++) //循环次数										
		{
			//对缓冲图像中间赋值
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
	}
	//选择公式二                                   //                            (delta(*))^2
	if (option == 2)                                 //   g(delta(*))=exp (-   -----------------------  )
	{                                              //                              (kappa)^2
		for (i = 0; i<Num; i++) //循环次数														
		{	//对缓冲图像中间赋值
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
					//对CN.......赋值				
					CN = (float)(1.0 / (1 + exp(-(DN*DN / temp_kappa))));
					CS = (float)(1.0 / (1 + exp(-(DS*DS / temp_kappa))));
					CE = (float)(1.0 / (1 + exp(-(DE*DE / temp_kappa))));
					CW = (float)(1.0 / (1 + exp(-(DW*DW / temp_kappa))));
					//最终结果
					temp = (float)(temp + lamba*(CN*DN +
						CS*DS +
						CE*DE +
						CW*DW));
					Pimgsource[k] = temp;
				}
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
			Pimgsource[lLBytes*y + x] = (unsigned char)temp1;
		}
	}

	float maxT = 1.0;
	//对结果图像进行归一化，扩大显示的对比度
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			if (Pimgsource[lLBytes*y + x]>maxT)
				maxT = Pimgsource[lLBytes*y + x];       // 计算图像的最高像素值
		}
	}

	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			image[lLBytes*y + x] = (unsigned char)(Pimgsource[lLBytes*y + x] * 255 / maxT);//对差值图像进行归一化
		}
	}
	delete[]Dff1;
	delete[]Pimgsource;
}

