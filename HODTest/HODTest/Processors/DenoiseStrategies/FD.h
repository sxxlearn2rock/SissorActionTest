#pragma once
#include "./Processors/DenoiseStrategy.h"

//�����㷨
class FD : public DenoiseStrategy
{
public:

	~FD(void) {}

	static FD* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new FD();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	FD(void) {}
	static FD* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(FD::mSingleton)  
				delete FD::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void fd(unsigned char* image, int height, int width);
};
