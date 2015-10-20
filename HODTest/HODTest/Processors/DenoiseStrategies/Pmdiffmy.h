#pragma once
#include "./Processors/DenoiseStrategy.h"

//�Ľ��͸��������˲�
class Pmdiffmy : public DenoiseStrategy
{
public:

	~Pmdiffmy(void) {}

	static Pmdiffmy* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Pmdiffmy();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	Pmdiffmy(void) {}
	static Pmdiffmy* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(Pmdiffmy::mSingleton)  
				delete Pmdiffmy::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void pmdiffmy(unsigned char* image, int height, int width);
};
