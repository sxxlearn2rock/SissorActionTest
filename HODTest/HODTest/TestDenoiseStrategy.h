#pragma once
#include "denoisestrategy.h"

//µ¥ÀýÄ£Ê½
class TestDenoiseStrategy : public DenoiseStrategy
{
public:	
	~TestDenoiseStrategy(void) {}
	static TestDenoiseStrategy* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new TestDenoiseStrategy();
		}
		return mSingleton;
	}

	void denoise(const Mat& srcImg, Mat& desImg);
private:
	TestDenoiseStrategy(void) : mArg(5) {}
	static TestDenoiseStrategy* mSingleton;

	int mArg;

	class Cleaner
	{
	public:
		~Cleaner()
		{
			if ( TestDenoiseStrategy::mSingleton != NULL )
			{
				delete TestDenoiseStrategy::mSingleton;
			}
		}
	};
	static Cleaner cleaner;

};

