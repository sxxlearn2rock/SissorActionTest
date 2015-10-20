#pragma once
#include "./Processors/DenoiseStrategy.h"

//ֱ��ͼ˫�������ǿ
class DoublehistEqual : public DenoiseStrategy
{
public:

	~DoublehistEqual(void) {}

	static DoublehistEqual* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DoublehistEqual();
		}
		return mSingleton;
	}

	//���Ĵ�����
	void denoise(const Mat& srcImg, Mat& desImg);
private:
	DoublehistEqual(void) {}
	static DoublehistEqual* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(DoublehistEqual::mSingleton)  
				delete DoublehistEqual::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void histEqual2(unsigned char *image, int height, int width );
	void imfilter(float *pimgsorce, float *image1, int width, int height, int *moban);
};
