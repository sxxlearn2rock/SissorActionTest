#include "./Processors/DenoiseStrategies/TDLMS.h"
#define PI 3.1415926535

//类静态变量必须在.cpp文件里声明
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
	//用5×5的固定加权模板去预测背景
	int ll = 3;
	int LL = 7;
	int N = LL*LL;
	float mu = 0.000001f; //收敛因子
	float *Weight = new float[N];
	float temp = 1.f / float(N - 1);
	for (int k = 0; k<N; k++)
	{
		Weight[k] = temp;
	}
	//进行LMS预测
	float p;
	float e;
	float sum;
	for (y = ll; y<height - ll; y++)
	{
		for (x = ll; x<width - ll; x++)
		{
			//1.得到预测值
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
			//2.得到残差
			e = float(OutImage[y*lLBytes + x]) - float(image[y*lLBytes + x]);
			//3.更新权值
			for (j = -ll; j <= ll; j++)
			{
				for (i = -ll; i <= ll; i++)
				{
					k1 = (y + j)*lLBytes + (x + i);
					k2 = (j + ll)*LL + (i + ll);
					Weight[k2] = Weight[k2] - 2 * mu*e*image[k1];
				}
			}
			//4.权值归一化

		}
	}
	//	memcpy(image,OutImage,sizeof(unsigned char)*lLBytes*height);
	//原图与背景做差，并归一化
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			float temp1;                                   //差图
			temp1 = float(image[lLBytes*y + x] - OutImage[lLBytes*y + x]);  //用原始图像减去背景图像
			if (temp1<0.0)
				temp1 = 0;
			if (temp1>255.0)
				temp1 = 255.0;
			OutImage[lLBytes*y + x] = (unsigned char)temp1;
		}
	}

	float maxT = 1.0;
	//对结果图像进行归一化，扩大显示的对比度
	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			if (OutImage[lLBytes*y + x]>maxT)
				maxT = OutImage[lLBytes*y + x];       // 计算图像的最高像素值
		}
	}

	for (y = 0; y<height; y++)
	{
		for (x = 0; x<width; x++)
		{
			image[lLBytes*y + x] = (unsigned char)(OutImage[lLBytes*y + x] * 255 / maxT);//对差值图像进行归一化
		}
	}
	delete[] Weight;
	delete[] OutImage;
}

