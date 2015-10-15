#pragma once
#include "DenoiseProcessor.h"

class DefaultDenosieProcessor : public DenoiseProcessor
{
public:

	~DefaultDenosieProcessor(void) {}

	static DefaultDenosieProcessor* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DefaultDenosieProcessor();
		}
		return mSingleton;
	}

	void denoise(const Mat& srcImg, Mat& desImg);
private:
		DefaultDenosieProcessor(void) {}
		static DefaultDenosieProcessor* mSingleton;

		class CGarbo   //��˽����Ƕ���Ψһ��������������������ɾ������
		{  
		public:  
			~CGarbo()  
			{  
				if(DefaultDenosieProcessor::mSingleton)  
					delete DefaultDenosieProcessor::mSingleton;  
			}  
		};  
		static CGarbo Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  
};
