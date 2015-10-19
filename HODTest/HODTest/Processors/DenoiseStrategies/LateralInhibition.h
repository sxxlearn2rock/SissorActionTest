#pragma once
#include "./Processors/DenoiseStrategy.h"

//����ģʽ
class LateralInhibition : public DenoiseStrategy
{
public:

	~LateralInhibition(void) {}

	static LateralInhibition* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new LateralInhibition();
		}
		return mSingleton;
	}


	void denoise( Mat& srcImg, Mat& desImg);

	void setKsize(int ksize) { mKsize = ksize; }
private:
	LateralInhibition(void) : mKsize(5){}
	static LateralInhibition* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(LateralInhibition::mSingleton)  
				delete LateralInhibition::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void lateralInhibition(unsigned char* image, int height, int width, int Ksize);
	int mKsize;
};
