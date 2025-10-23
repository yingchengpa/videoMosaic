
#pragma once

#ifdef  __cplusplus
extern "C" {
#endif


#if defined(WIN32)  /* windows */
#define EXPORT_API                  __declspec(dllexport)
#else
#define EXPORT_API                  __declspec(dllimport)
#endif

/* 函数标准调用约定 Standard function calling convention */
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
* 说明: 版本为x64版本，基于vs2022，使用前需要先安装依赖库 VC_redist15-17-19-22.x64.exe
* 中文编码格式为utf8
*/

#define errcode_success 0

/*
* @brief 初始化，必须，不可重复调用
*/
EXPORT_API int STDCALL libfcdetec_init(char* auth);

/*
* @brief 输入图片，返回人脸坐标
* data ：图片二进制信息 图像必须为BGR三通道的图像，而非rgb图像
* return char* 目标坐标json
*/
EXPORT_API char* STDCALL libfcdetec_fcdection_img(char* img_name);

/*
* @brief 分析Mat信息
* return char* 目标坐标json
*/
EXPORT_API char* STDCALL libfcdetec_fcdection_Mat(int rows, int cols, int type, void* data);


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */