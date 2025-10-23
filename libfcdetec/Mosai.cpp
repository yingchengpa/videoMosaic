
#include "Mosaic.h"

bool Generate_Mosaic(cv::Mat& src, std::list<CFaceP>& faces)
{
	if (faces.empty()) {
		return false;
	}

	int step = 10;//����

	for(auto it = faces.begin();it!=faces.end();++it)
	{
		int x = (it->x*src.cols)/10000; //�������ο����x����
		int y = (it->y*src.rows)/10000;//�������ο����y����
		int width = (it->w*src.cols)/10000;//�������ο��
		int height = (it->h*src.rows)/10000;//�������ο��

		//��Χ�����ߵ� 10%

		x = x - width * 0.1;
		y = y - height * 0.1;
		width = width * 1.2;
		height = height * 1.2;

		// Խ�籣��
		if (x + width + step > src.cols) {
			width = src.cols - x - step;
		}
		if (y + height + step > src.rows) {
			height = src.rows - y - step;
		}

		//int x = (it->x ); //�������ο����x����
		//int y = (it->y  );//�������ο����y����
		//int width = (it->w) ;//�������ο��
		//int height = (it->h ) ;//�������ο��

		//��������������������޸ġ������������ο��������أ�����������޸�
		for (int i = y; i < (y + height); i += step)
		{
			for (int j = x; j < (x + width); j += step)
			{
				//���������ο���ϸ��Ϊ���ɸ�С���飬���ζ�ÿ�������޸����أ���ͬ���鸳����ͬ�Ҷ�ֵ��
				for (int k = i; k < (step + i); k++)
				{
					for (int m = j; m < (step + j); m++)
					{
						//�Ծ�����������ֵ�����޸ģ�rgb��ͨ��
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