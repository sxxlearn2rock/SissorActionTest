#pragma once
#include "./Processors/strategies.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//����ģʽ
class DenoiseProcessor
{
public:
	~DenoiseProcessor(void) {}

	static DenoiseProcessor* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new DenoiseProcessor;
		}
		return mSingleton;
	}

	void setDenoiseStrategy(DenoiseStrategy* denoiseStrategy) { mDenoiseStrategy = denoiseStrategy; }

	void process(Mat& inputImg, Mat& outputImg);
private:
	DenoiseProcessor(void) {}
	DenoiseProcessor(DenoiseStrategy* denoiseStrategy) { mDenoiseStrategy = denoiseStrategy; }

	class Cleaner   //��˽����Ƕ���Ψһ��������������������ɾ������
	{  
	public:  
		~Cleaner()  
		{  
			if(DenoiseProcessor::mSingleton)  
				delete DenoiseProcessor::mSingleton;  
		}  
	};  
	static Cleaner cleaner;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  

	static DenoiseProcessor* mSingleton;
	DenoiseStrategy* mDenoiseStrategy;
};

