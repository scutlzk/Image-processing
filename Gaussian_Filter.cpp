//高斯滤波器    https://github.com/scutlzk
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <vector>

using namespace  cv;
using namespace  std;


void Get_Gaussian_Kernel(double*& gaus_1, const int size, const double sigma_s)
{
	gaus_1 = new double[size*size];
	double **gaus = new double*[size];
	for (int i = 0; i<size; i++)gaus[i] = new double[size];

	double sum = 0;
	for (int i = -size / 2; i<size / 2 + 1; i++) {
		for (int j = -size / 2; j<size / 2 + 1; j++) {
			gaus[i + size / 2][j + size / 2] = exp(-((i*i) + (j*j)) / (2 * sigma_s*sigma_s));
			sum += gaus[i + size / 2][j + size / 2];
		}
	}

	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			gaus[i][j] /= sum;
			gaus_1[i*size + j] = gaus[i][j];	//使用一维更简单
		}
	}
	
	return;
}


void Gaussian_Filter(const char *filename, Mat *&dst,const int size,const double sigma_s)
{
	double* templates;
	Get_Gaussian_Kernel(templates, size, sigma_s);
	Mat src = imread(filename, 3); 
	dst = new Mat(src.rows, src.cols, CV_8UC3);
	namedWindow("src");
	imshow("src", src);
	for (int j = 0; j<src.rows; j++)  
	{
		for (int i = 0; i<src.cols; i++)
		{
			double sum0 = 0;
			double sum1 = 0;
			double sum2 = 0;
			int index = 0;
			for (int m = j - size/2; m<j + size/2+1; m++)
			{
				for (int n = i - size / 2; n<i + size / 2 + 1; n++)
				{
					
					if (m<0 || n<0 || m>src.rows - 1 || n>src.cols - 1) { index++; continue; }//边缘不处理  
					sum0 += src.at<Vec3b>(m, n)[0] * templates[index++];
					sum1 += src.at<Vec3b>(m, n)[1] * templates[index-1];
					sum2 += src.at<Vec3b>(m, n)[2] * templates[index-1];

				}
			}
			sum0 > 255 ? 255 : sum0;
			sum1 > 255 ? 255 : sum1;
			sum2 > 255 ? 255 : sum2;

			(*dst).at<Vec3b>(j, i)[0] = sum0;
			(*dst).at<Vec3b>(j, i)[1] = sum1;
			(*dst).at<Vec3b>(j, i)[2] = sum2;
		}
	}
	
	namedWindow("dst");
	imshow("dst", *dst);
	waitKey(0);
	return;
 }









int main() {
	const char *filename = "123.jpg";
	const int Gaussian_Kernel_Size = 9;
	const double sigma_s = 3;

	Mat *dst;
	Gaussian_Filter(filename, dst, Gaussian_Kernel_Size, sigma_s);
	imwrite("1234.jpg", *dst);
	return 0;

}

