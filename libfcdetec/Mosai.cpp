
#include "Mosaic.h"

bool Generate_Mosaic(cv::Mat& src, std::list<CFaceP>& faces)
{
	if (faces.empty()) {
		return false;
	}

	int step = 10;//步长

	for(auto it = faces.begin();it!=faces.end();++it)
	{
		int x = (it->x*src.cols)/10000; //人脸矩形框起点x坐标
		int y = (it->y*src.rows)/10000;//人脸矩形框起点y坐标
		int width = (it->w*src.cols)/10000;//人脸矩形框宽
		int height = (it->h*src.rows)/10000;//人脸矩形框高

		//范围扩大宽高的 10%

		x = x - width * 0.1;
		y = y - height * 0.1;
		width = width * 1.2;
		height = height * 1.2;

		// 越界保护
		if (x + width + step > src.cols) {
			width = src.cols - x - step;
		}
		if (y + height + step > src.rows) {
			height = src.rows - y - step;
		}

		//int x = (it->x ); //人脸矩形框起点x坐标
		//int y = (it->y  );//人脸矩形框起点y坐标
		//int width = (it->w) ;//人脸矩形框宽
		//int height = (it->h ) ;//人脸矩形框高

		//仅对人脸区域进行像素修改。遍历人脸矩形框区域像素，并对其进行修改
		for (int i = y; i < (y + height); i += step)
		{
			for (int j = x; j < (x + width); j += step)
			{
				//将人脸矩形框再细分为若干个小方块，依次对每个方块修改像素（相同方块赋予相同灰度值）
				for (int k = i; k < (step + i); k++)
				{
					for (int m = j; m < (step + j); m++)
					{
						//对矩形区域像素值进行修改，rgb三通道
						for (int c = 0; c < 3; c++)
						{
							src.at<cv::Vec3b>(k, m)[c] = src.at<cv::Vec3b>(i, j)[c];
						}
					}
				}
			}
		}
	}

	return true;
}