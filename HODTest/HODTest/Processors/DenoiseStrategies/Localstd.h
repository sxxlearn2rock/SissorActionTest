#pragma once
#include "./Processors/DenoiseStrategy.h"

//���ھֲ����������
class Localstd : public DenoiseStrategy
{
public:

	~Localstd(void) {}

	static Localstd* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Localstd();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

	void setKsize(int ksize) { mKsize = ksize; }
private:
	Localstd(void) : mKsize(5){}
	static Localstd* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(Localstd::mSingleton)  
				delete Localstd::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void localstd(unsigned char* image, int height, int width, int Ksize);
	int mKsize;
};
