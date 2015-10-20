#pragma once
#include "./Processors/DenoiseStrategy.h"

//�ֿ�������󻯱�������
class LMPM : public DenoiseStrategy
{
public:

	~LMPM(void) {}

	static LMPM* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new LMPM();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	LMPM(void) {}
	static LMPM* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(LMPM::mSingleton)  
				delete LMPM::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void lmpm(unsigned char* image, int height, int width);
};
