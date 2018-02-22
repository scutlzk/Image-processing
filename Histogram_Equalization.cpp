
//直方图均衡化	https://github.com/scutlzk
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include<vector>

using namespace  cv;
using namespace  std;
double gray[256];
const char *a = "123.jpg";
int main(){

	Mat src = imread(a, 0);
	vector<uchar> array(src.rows*src.cols);
	if (src.isContinuous())  {array.assign(src.datastart, src.dataend);}
	
	for (int i = 0; i < src.rows*src.cols; i++)++gray[array[i]];

	for (int i = 0; i < 256; i++) {
		gray[i] /= (src.rows*src.cols);
		gray[i] = int(255 * gray[i]+0.5);
		if (i > 0)gray[i] = (gray[i] + gray[i - 1]);
	}

	for (int i = 0; i < src.rows*src.cols; i++)array[i] = gray[array[i]];

	Mat dst((int)src.rows,(int)src.cols, 0);
	for (int i = 0; i < src.rows; i++) 
		for (int j = 0; j <  src.cols; j++) 
			dst.at<uchar>(i, j) = array[i*src.cols+j];


	imwrite("dst.jpg", dst);
	namedWindow("src");
	imshow("src", src);
	namedWindow("dst");
	imshow("dst", dst);
	waitKey(0);
	system("pause"); 

	return 0;

}

