#include "./Processors/SegmentStrategy.h"

void SegmentStrategy::morphFilter( Mat& srcImage, Mat &dstImage, int erosionType, int dilationType, int erosionSize, int dilationSize )
{
	Mat element_erosion = cv::getStructuringElement( erosionType,  //��ʴ�����ں���״: MORPH_RECT=0, MORPH_CROSS=1, MORPH_ELLIPSE=2
		cv::Size( 2 * erosionSize + 1, 2 * erosionSize + 1 ),                     //��ʴ�����ں˳ߴ�
		cv::Point( -1, -1 ) );                                                                    //��ʴ����ê��λ��

	Mat element_dilation = cv::getStructuringElement( dilationType,//���Ͳ����ں���״
		cv::Size( 2*dilationSize + 1, 2*dilationSize + 1 ),                       //���Ͳ����ں˳ߴ�
		cv::Point( -1, -1 ) );                                                                  //���Ͳ���ê��λ��
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
	 findContours(prImage,                                               // ͼ��  
		                  contours,                                               // ������  
		                                                                               // ����ͼ�����˽ṹ����Ϣ����ѡ����������û��ѡ��  
		CV_RETR_EXTERNAL,                                                // ��ȡ�����ķ����������ȡ��Χ������  
		CV_CHAIN_APPROX_NONE);                                    // �������Ƶķ��������ﲻ���ƣ���ȡȫ��������

	//�������Ϣmom��ȷ���ʵ�λ��Point������ǳ�Բ��  
	std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin(); 
	while(itc != contours.end())  
	{            
		cv::Moments mom = moments(Mat(*itc++));   //�������еľ� 
		coordinate.setCenterX(mom.m10/mom.m00);
		coordinate.setCenterY(mom.m01/mom.m00);
		coordinates.push_back(coordinate);
		//cv::circle(dstImage, cv::Point(mom.m10/mom.m00, mom.m01/mom.m00), 1, cv::Scalar(255), 1);//���㲢��������
	}

	drawContours(dstImage, contours, -1, cv::Scalar(255), 2); // ��ԭͼ�ϻ���������

	//�������������Χ���β�����
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
	//Ѱ�����ӵ�
	Mat srcImg;
	cv::Point point;
	srcBw.copyTo(srcImg);
	for(int j = 0; j < srcImg.rows; j++)
	{
		float* ptr = srcImg.ptr<float>(j);
		for(int i = 0; i < srcImg.cols; i++)
		{
			if(ptr[i])
				point.x = i;//���ӵ�����λ��
			    point.y = j;
		}
	}	

	cv::Size m_Size = srcBw.size();
	Mat Temp=Mat::zeros(m_Size.height+2, m_Size.width+2, srcBw.type());//��չͼ��
	srcBw.copyTo(Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)));
	cv::floodFill(Temp, point, cv::Scalar(255));//��ˮ���

	Mat cutImg;//�ü���չ��ͼ��
	Temp(cv::Range(1, m_Size.height + 1), cv::Range(1, m_Size.width + 1)).copyTo(cutImg);
	dstBw = srcBw | (~cutImg);//��������
}