#pragma once

#include "face_func.h"
#include "libfacedetection/facedetectcnn.h"

#include <Windows.h>

unsigned char* s_p_point_buff = nullptr;  //multiple threads


/*
* 调试器优化方法：
* c++下的优化选的-速度最大化/o2 , 代码速度优先; 代码生成下 启动增强指令集 选AVX2，浮点模型选 快速， 语言下openmp选是。
* *如果使用Intel CPU或NEON for ARM ，可以开启 AVX2
*/
std::list<CFaceP> 	get_face_p_by_cnn(cv::Mat* pMat) {

	ULONG64 ulNow = GetTickCount64();
	if (s_p_point_buff == nullptr)
	{
		s_p_point_buff = new unsigned char[0x20000];
	}

	int* pResults = nullptr; //用来检测人脸
	pResults = facedetect_cnn(s_p_point_buff, (unsigned char*)(pMat->ptr(0)), pMat->cols, pMat->rows, pMat->step);
	//利用facedetect_cnn函数来获取人脸，用于存储人脸检测结果的缓冲存储器！其大小必须为0x20000字节
	//facedetect_cnn函数识别的图像必须为BGR三通道的图像，而非rgb图像
	std::list<CFaceP> resList;
	for (int i = 0; i < (pResults ? (*pResults) : 0); i++) {
		//如果pResult为NULL,即pResult没有检测到人脸，就返回0，for循环结束
		short* p = ((short*)(pResults + 1)) + (142 * i);
		//p指针用来指向
		if (p[0] >= s_score) {
			CFaceP res;
			res.sScore = p[0];	  //显示脸的置信度。其范围为[0-100]
			res.x = (p[1]*10000)/ pMat->cols;
			res.y = (p[2]*10000)/ pMat->rows;
			res.w = (p[3]*10000)/ pMat->cols;
			res.h = (p[4]*10000)/ pMat->rows;

			resList.push_back(res);
		}
	}

	//printf("--  %llu  ----\n", GetTickCount64() - ulNow);
	return resList;
}