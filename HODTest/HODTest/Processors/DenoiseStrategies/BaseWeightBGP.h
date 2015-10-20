#pragma once
#include "./Processors/DenoiseStrategy.h"

//�̶�Ȩֵ����Ԥ��
class BaseWeightBGP : public DenoiseStrategy
{
public:

	~BaseWeightBGP(void) {}

	static BaseWeightBGP* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new BaseWeightBGP();
		}
		return mSingleton;
	}


	void denoise(const Mat& srcImg, Mat& desImg);

private:
	BaseWeightBGP(void) {}
	static BaseWeightBGP* mSingleton;

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(BaseWeightBGP::mSingleton)  
				delete BaseWeightBGP::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	void baseweightbgp(unsigned char* image, int height, int width);
};
