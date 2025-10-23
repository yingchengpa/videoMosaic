#pragma once

#include "face_func.h"
#include "libfacedetection/facedetectcnn.h"

#include <Windows.h>

unsigned char* s_p_point_buff = nullptr;  //multiple threads


/*
* �������Ż�������
* c++�µ��Ż�ѡ��-�ٶ����/o2 , �����ٶ����ȣ����������� ������ǿָ� ѡAVX2������ģ��ѡ ���٣� ������openmpѡ�ǡ�
* *���ʹ��Intel CPU��NEON for ARM �����Կ��� AVX2
*/
std::list<CFaceP> 	get_face_p_by_cnn(cv::Mat* pMat) {

	ULONG64 ulNow = GetTickCount64();
	if (s_p_point_buff == nullptr)
	{
		s_p_point_buff = new unsigned char[0x20000];
	}

	int* pResults = nullptr; //�����������
	pResults = facedetect_cnn(s_p_point_buff, (unsigned char*)(pMat->ptr(0)), pMat->cols, pMat->rows, pMat->step);
	//����facedetect_cnn��������ȡ���������ڴ洢����������Ļ���洢�������С����Ϊ0x20000�ֽ�
	//facedetect_cnn����ʶ���ͼ�����ΪBGR��ͨ����ͼ�񣬶���rgbͼ��
	std::list<CFaceP> resList;
	for (int i = 0; i < (pResults ? (*pResults) : 0); i++) {
		//���pResultΪNULL,��pResultû�м�⵽�������ͷ���0��forѭ������
		short* p = ((short*)(pResults + 1)) + (142 * i);
		//pָ������ָ��
		if (p[0] >= s_score) {
			CFaceP res;
			res.sScore = p[0];	  //��ʾ�������Ŷȡ��䷶ΧΪ[0-100]
			res.x = (p[1]*10000)/ pMat->cols;
			res.y = (p[2]*10000)/ pMat->rows;
			res.w = (p[3]*10000)/ pMat->cols;
			res.h = (p[4]*10000)/ pMat->rows;
			//res.x = (p[1] ) ;
			//res.y = (p[2] );
			//res.w = (p[3] ) ;
			//res.h = (p[4] ) ;
			resList.push_back(res);
		}
	}

	//printf("--  %llu  ----\n", GetTickCount64() - ulNow);
	return resList;
}