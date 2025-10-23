#pragma once

#include "face_func.h"
#include <opencv2/opencv.hpp>

bool Generate_Mosaic(cv::Mat& src, std::list<CFaceP>& faces);

