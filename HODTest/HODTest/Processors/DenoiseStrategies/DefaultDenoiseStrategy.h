#pragma once
#include "./Processors/DenoiseStrategy.h"

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

		class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
		{  
		public:  
			~Cleaner()  
			{  
				if(DefaultDenosieStrategy::mSingleton)  
					delete DefaultDenosieStrategy::mSingleton;  
			}  
		};  
		static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

		int mArg1;
};
