#pragma once
#include "denoisestrategy.h"

//µ¥ÀýÄ£Ê½
class TestDenoiseStrategy2 : public DenoiseStrategy
{
public:	
	~TestDenoiseStrategy2(void) {}
	static TestDenoiseStrategy2* getInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new TestDenoiseStrategy2();
		}
		return mSingleton;
	}

	void denoise(const Mat& srcImg, Mat& desImg);
private:
	TestDenoiseStrategy2(void) : mArg(10) {}
	static TestDenoiseStrategy2* mSingleton;

	int mArg;

	class Cleaner
	{
	public:
		~Cleaner()
		{
			if ( TestDenoiseStrategy2::mSingleton != NULL )
			{
				delete TestDenoiseStrategy2::mSingleton;
			}
		}
	};
	static Cleaner cleaner;

};
