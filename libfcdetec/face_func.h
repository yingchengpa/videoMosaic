#pragma once

#include <list>
#include "opencv2/opencv.hpp"

const int s_score = 80;

class CFaceP
{
public:
	int sScore = 0;
	int x = 0;		 // 万分比
	int y = 0;		 // 万分比
	int w = 0;		 // 万分比
	int h = 0;		 // 万分比
};

// 基于libfacedetection 开源库做的人脸检测
std::list<CFaceP> 	get_face_p_by_cnn(cv::Mat *pMat);