#pragma once
#include "./Processors/DenoiseStrategy.h"

//���ھֲ���ֵ�Աȶȱ�������
class LocalMeanContrast : public DenoiseStrategy
{
public:

	~LocalMeanContrast(void) {}

	static LocalMeanContrast* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new LocalMeanContrast();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

	void setKsize(int ksize1 , int ksize2) 
	{
		mKsize1 = ksize1; 
		mKsize2 = ksize2; 
	}

private:
	LocalMeanContrast(void) : mKsize1(5) , mKsize2(11){}
	static LocalMeanContrast* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(LocalMeanContrast::mSingleton)  
				delete LocalMeanContrast::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void localmeancontrast(unsigned char* image, int height, int width, int Ksize1, int Ksize2);
	int mKsize1;
	int mKsize2;
};


