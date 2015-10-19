#pragma once
#include "./Processors/DenoiseStrategy.h"

//����ģʽ
class Pmdiff2 : public DenoiseStrategy
{
public:

	~Pmdiff2(void) {}

	static Pmdiff2* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Pmdiff2();
		}
		return mSingleton;
	}

	//���Ĵ�����
	void denoise( Mat& srcImg, Mat& desImg);
private:
	Pmdiff2(void) {}
	static Pmdiff2* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(Pmdiff2::mSingleton)  
				delete Pmdiff2::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void pm(unsigned char *image, int height, int width );
	void imfilter(float *pimgsorce, float *image1, int width, int height, int *moban);
};
