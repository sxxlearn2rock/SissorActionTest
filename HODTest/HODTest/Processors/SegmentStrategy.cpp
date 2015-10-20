#include "./Processors/SegmentStrategy.h"

void SegmentStrategy::morphFilter( Mat& srcImage, Mat &dstImage, int erosionType, int dilationType, int erosionSize, int dilationSize )
{
	Mat element_erosion = cv::getStructuringElement( erosionType,  //腐蚀操作内核形状: MORPH_RECT=0, MORPH_CROSS=1, MORPH_ELLIPSE=2
		cv::Size( 2 * erosionSize + 1, 2 * erosionSize + 1 ),                     //腐蚀操作内核尺寸
		cv::Point( -1, -1 ) );                                                                    //腐蚀操作锚点位置

	Mat element_dilation = cv::getStructuringElement( dilationType,//膨胀操作内核形状
		cv::Size( 2*dilationSize + 1, 2*dilationSize + 1 ),                       //膨胀操作内核尺寸
		cv::Point( -1, -1 ) );                                                                  //膨胀操作锚点位置
	cv::erode(srcImage, dstImage, element_erosion);
	fillHole(dstImage, dstImage);
	cv::dilate(dstImage, dstImage, element_dilation);
	fillHole(dstImage, dstImage);
}

void SegmentStrategy::positionResult( Mat &srcImage, Mat &dstImage, std::vector<Coordinate>& coordinates, std::vector<cv::RotatedRect>& rotatedRects )
{
	std::vector<std::vector<cv::Point>> contours;
	 Coordinate coordinate;
	 Mat prImage;
	 srcImage.copyTo(prImage);
	 findContours(prImage,                                               // 图像  
		                  contours,                                               // 轮廓点  
		                                                                               // 包含图像拓扑结构的信息（可选参数，这里没有选）  
		CV_RETR_EXTERNAL,                                                // 获取轮廓的方法（这里获取外围轮廓）  
		CV_CHAIN_APPROX_NONE);                                    // 轮廓近似的方法（这里不近似，获取全部轮廓）

	//计算矩信息mom，确定质点位置Point，并标记成圆点  
	std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin(); 
	while(itc != contours.end())  
	{            
		cv::Moments mom = moments(Mat(*itc++));   //计算所有的矩 
		coordinate.setCenterX(mom.m10/mom.m00);
		coordinate.setCenterY(mom.m01/mom.m00);
		coordinates.push_back(coordinate);
		//cv::circle(dstImage, cv::Point(mom.m10/mom.m00, mom.m01/mom.m00), 1, cv::Scalar(255), 1);//计算并画出质心
	}

	drawContours(dstImage, contours, -1, cv::Scalar(255), 2); // 在原图上画出轮廓线

	//计算轮廓点的外围矩形并画出
	for( int i = 0; i < contours.size(); i++ )
	{ 
		rotatedRects.push_back(minAreaRect( Mat(contours[i]) )) ;
	}

	cv::Point2f rect_points[4]; 
	for( int i = 0; i < rotatedRects.size(); i++ )
	{
		rotatedRects[i].points( rect_points );
		for( int j = 0; j < 4; j++ )
		cv::line(dstImage, rect_points[j], rect_points[(j+1)%4], cv::Scalar(255), 1, 8 );		
	}

	/*std::vector<cv::Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
	boundRect[i] = boundingRect( Mat(contours[i]) );
	}
	for (int i = 0; i < contours.size(); i++)
	{
	rectangle(dstImage, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(255), 1 ,8);
	}*/
	contours.clear();
}

void SegmentStrategy::fillHole(const Mat& srcBw, Mat &dstBw)
{	
	//寻找种子点
	Mat srcImg;
	cv::Point point;
	srcBw.copyTo(srcImg);
	for(int j = 0; j < srcImg.rows; j++)
	{
		float* ptr = srcImg.ptr<float>(j);
		for(int i = 0; i < srcImg.cols; i++)
		{
			if(ptr[i])
				point.x = i;//种子点坐标位置
			    point.y = j;
		}
	}	

	cv::Size m_Size = srcBw.size();
	Mat Temp=Mat::zeros(m_Size.height+2, m_Size.width+2, srcBw.type());//延展图像
	srcBw.copyTo(Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)));
	cv::floodFill(Temp, point, cv::Scalar(255));//漫水填充

	Mat cutImg;//裁剪延展的图像
	Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)).copyTo(cutImg);
	dstBw = srcBw | (~cutImg);//条件膨胀
}