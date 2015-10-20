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
	SegmentStrategy(void) : mDilationSize(2), mDilationType(0), mErosionSize(2), mErosionType(0){}
	~SegmentStrategy(void) {}

	virtual void process(Mat& srcImg, Mat& segImg, Mat& desImg, 
		vector<Coordinate>& coordinates, vector<RotatedRect>& rotatedRects) = 0;

	void setErosionType(int type) { mErosionType = type; }
	void setDilationType(int type) { mDilationType = type; }
	void setErosionSize(int size) { mErosionSize = size; }
	void setDilationSize(int size) { mDilationSize = size; }

protected:
	//��̬ѧ�˲�����
	int mErosionType;
	int mDilationType;
	int mErosionSize;
	int mDilationSize;

	void morphFilter(Mat& srcImage, Mat &dstImage, int erosionType, int dilationType, int erosionSize, int dilationSize);
	void positionResult(Mat& srcImage, Mat &dstImage, std::vector<Coordinate>& coordinates, std::vector<cv::RotatedRect>& rotateRects);
	void fillHole(const Mat& srcBw, Mat &dstBw);
};






