#pragma once
#include <string>

using std::string;
//��Ƶ�������ĳ��࣬�涨������Ƶ�������ı�׼
abstract class VideoPlayer
{
public:
	virtual void readVideo(const std::string& filepath) = 0;

};