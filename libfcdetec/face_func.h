#pragma once

#include <list>
#include <opencv2/opencv.hpp>

const int s_score = 80;

class CFaceP
{
public:
	int sScore = 0;
	int x = 0;		 // ��ֱ�
	int y = 0;		 // ��ֱ�
	int w = 0;		 // ��ֱ�
	int h = 0;		 // ��ֱ�
};

// ����libfacedetection ��Դ�������������
std::list<CFaceP> 	get_face_p_by_cnn(cv::Mat *pMat);