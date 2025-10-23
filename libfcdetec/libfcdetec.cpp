
#include "pch.h"
#include "libfcdetec.h"

#include "json.hpp"
#include "face_func.h"
#include "Mosaic.h"

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <map>



using json = nlohmann::json;

static std::string s_last_str = "";
static int n_frame_count = 0;
static std::list<CFaceP> s_last_face;

class Mat_data {
public:
	int width = 0;
	int height = 0;
	int channel = 0;
	int n_frame = 0;
	long long p_data = 0;
};

void to_json(json& j, const CFaceP& r) {
	j = json{
		{"score", r.sScore},
		{"x", r.x},
		{"y", r.y},
		{"w", r.w},
		{"h", r.h}
		
	};
}

void to_json(json& j, const Mat_data& r) {
	j = json{
	   {"w", r.width},
		{"h", r.height},
		{"c", r.channel},
		{"d", r.p_data}	 ,
		{"f",r.n_frame}
	};
}

/*
* @brief ��ʼ�������룬�����ظ�����
*/
int STDCALL libfcdetec_init(char* auth)
{
	return 1;
}

/*
* @brief ����ͼƬ��������������
* return char* Ŀ������json
*/
char* STDCALL libfcdetec_fcdection_img(char* file_name)
{
	cv::Mat src, dst;
	src = cv::imread(file_name);  //������Ҫʶ���ͼ��

	std::list<CFaceP> oLast = get_face_p_by_cnn(&src);
	
	json j(oLast);
	s_last_str = j.dump();
	return (char*)s_last_str.c_str();
}

char* STDCALL libfcdetec_fcdection_Mat(int rows, int cols, int type, void* data)
{
	cv::Mat frame = cv::Mat(rows, cols, CV_8UC3, data);

	//ÿ10֡����һ�μ��
	if (n_frame_count % 10 == 0)
	{
		//���ţ���������	 
		cv::Mat result_cnn;
		cv::resize(frame, result_cnn, cv::Size(640, 480), 0, 0, cv::INTER_AREA);
		s_last_face = get_face_p_by_cnn(&result_cnn);
	}

	//����������
	Generate_Mosaic(frame, s_last_face);

	n_frame_count++;

	json j(s_last_face);
	s_last_str = j.dump();
	return (char*)s_last_str.c_str();
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
