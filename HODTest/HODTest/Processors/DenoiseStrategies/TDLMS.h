#pragma once
#include "./Processors/DenoiseStrategy.h"

//��������ӦȨֵ����Ԥ��
class TDLMS : public DenoiseStrategy
{
public:

	~TDLMS(void) {}

	static TDLMS* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new TDLMS();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	TDLMS(void) {}
	static TDLMS* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(TDLMS::mSingleton)  
				delete TDLMS::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void tdlms(unsigned char* image, int height, int width);
};
