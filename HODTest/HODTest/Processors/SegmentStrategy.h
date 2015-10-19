#pragma once
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::vector;
using cv::Mat;	using cv::RotatedRect;

//�����࣬���Դ洢���Ŀ�����������
class Coordinate
{
public:
	Coordinate(){}
	Coordinate(float x, float y) { mCenterX = x; mCenterY = y;}
	void setCenterX(float x) { mCenterX = x;}
	float getCenterX() {return mCenterX;}
	void setCenterY(float y) {mCenterY = y;}
	float getCenterY() {return mCenterY;}
private:
	float mCenterX;
	float mCenterY;
};

//���зָ�߿���ĳ��࣬������Ϊ���־���ķָ������
class SegmentStrategy
{
public:
	SegmentStrategy(void) {}
	~SegmentStrategy(void) {}

	virtual void process(Mat& srcImg, Mat& segImg,  Mat& desImg, vector<Coordinate> coordinates, vector<RotatedRect> rotatedRects) = 0;
};




