#pragma once
#include "DenoiseStrategy.h"

//����ģʽ
class DefaultDenosieStrategy : public DenoiseStrategy
{
public:

	~DefaultDenosieStrategy(void) {}

	static DefaultDenosieStrategy* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DefaultDenosieStrategy();
		}
		return mSingleton;
	}

	void setArg1(int arg) { mArg1 = arg; }

	void denoise(const Mat& srcImg, Mat& desImg);
private:
		DefaultDenosieStrategy(void) : mArg1(5) {}
		static DefaultDenosieStrategy* mSingleton;

		class CGarbo   //��˽����Ƕ���Ψһ��������������������ɾ������
		{  
		public:  
			~CGarbo()  
			{  
				if(DefaultDenosieStrategy::mSingleton)  
					delete DefaultDenosieStrategy::mSingleton;  
			}  
		};  
		static CGarbo Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

		int mArg1;
};
