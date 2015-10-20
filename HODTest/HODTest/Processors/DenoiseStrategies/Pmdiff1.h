#pragma once
#include "./Processors/DenoiseStrategy.h"

//һά���������˲�
class Pmdiff1 : public DenoiseStrategy
{
public:

	~Pmdiff1(void) {}

	static Pmdiff1* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new Pmdiff1();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	Pmdiff1(void) {}
	static Pmdiff1* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(Pmdiff1::mSingleton)  
				delete Pmdiff1::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void pmdiff1(unsigned char* image, int height, int width);
};
