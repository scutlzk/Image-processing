
//直方图均衡化	https://github.com/scutlzk
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include<vector>
using namespace  cv;
using namespace  std;


void Histogram_Equalization(const char *srcfilename, Mat *&dst)
{
	double gray[256];
	Mat src = imread(srcfilename, 0);
	vector<uchar> array(src.rows*src.cols);
	if (src.isContinuous()) { array.assign(src.datastart, src.dataend); }

	for (int i = 0; i < src.rows*src.cols; i++)++gray[array[i]];

	for (int i = 0; i < 256; i++) {
		gray[i] /= (src.rows*src.cols);
		gray[i] = int(255 * gray[i] + 0.5);
		if (i > 0)gray[i] = (gray[i] + gray[i - 1]);
	}

	for (int i = 0; i < src.rows*src.cols; i++)array[i] = gray[array[i]];

	dst=new Mat((int)src.rows, (int)src.cols, 0);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			dst->at<uchar>(i, j) = array[i*src.cols + j];
	
	namedWindow("src");
	imshow("src", src);
	namedWindow("dst");
	imshow("dst", *dst);
	waitKey(0);
	return ;
}
int main(){
	const char *filename = "123.jpg";//待处理文件名
	Mat *dst;
	Histogram_Equalization(filename, dst);
	imwrite("dst.jpg", *dst);
}

