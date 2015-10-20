#pragma once
#include "./Processors/DenoiseStrategy.h"

//�����ֵ�˲�
class MaxMedianFilter : public DenoiseStrategy
{
public:

	~MaxMedianFilter(void) {}

	static MaxMedianFilter* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new MaxMedianFilter();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	MaxMedianFilter(void) {}
	static MaxMedianFilter* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(MaxMedianFilter::mSingleton)  
				delete MaxMedianFilter::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void maxmedianfilter(unsigned char* image, int height, int width);
};
