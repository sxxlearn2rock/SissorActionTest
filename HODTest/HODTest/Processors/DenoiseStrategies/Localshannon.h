#pragma once
#include "./Processors/DenoiseStrategy.h"

//���ھֲ��ر�������
class Localshannon : public DenoiseStrategy
{
public:

	~Localshannon(void) {}

	static Localshannon* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Localshannon();
		}
		return mSingleton;
	}

	//���Ĵ�����
	void denoise(const Mat& srcImg, Mat& desImg);
	void setKsize(int ksize) { mKsize = ksize; }

private:
	Localshannon(void) : mKsize(5){}
	static Localshannon* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(Localshannon::mSingleton)  
				delete Localshannon::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void localshannon(unsigned char *image, int width, int height, int LL);
	int mKsize;
};
