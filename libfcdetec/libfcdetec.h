
#pragma once

#ifdef  __cplusplus
extern "C" {
#endif


#if defined(WIN32)  /* windows */
#define EXPORT_API                  __declspec(dllexport)
#else
#define EXPORT_API                  __declspec(dllimport)
#endif

/* ������׼����Լ�� Standard function calling convention */
#ifdef i386
#ifndef STDCALL
#define STDCALL                 __attribute__((stdcall))
#endif
#else
#ifndef WIN32
#ifndef STDCALL
#define STDCALL
#endif
#else
#ifndef STDCALL
#define STDCALL                 __stdcall
#endif
#endif

#endif

/*
* ˵��: �汾Ϊx64�汾������vs2022��ʹ��ǰ��Ҫ�Ȱ�װ������ VC_redist15-17-19-22.x64.exe
* ���ı����ʽΪutf8
*/

#define errcode_success 0

/*
* @brief ��ʼ�������룬�����ظ�����
*/
EXPORT_API int STDCALL libfcdetec_init(char* auth);

/*
* @brief ����ͼƬ��������������
* data ��ͼƬ��������Ϣ ͼ�����ΪBGR��ͨ����ͼ�񣬶���rgbͼ��
* return char* Ŀ������json
*/
EXPORT_API char* STDCALL libfcdetec_fcdection_img(char* img_name);

/*
* @brief ����Mat��Ϣ
* return char* Ŀ������json
*/
EXPORT_API char* STDCALL libfcdetec_fcdection_Mat(int rows, int cols, int type, void* data);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */