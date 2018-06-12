#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main(){
	string files = "lena.jpg";
	Mat img = imread(files, 0);
	int Height = img.cols;
	int Width = img.rows;
	int depth = 1;
	int depthcount = 1;
	Mat tmp = Mat::ones(Width, Height, CV_32FC1);
	Mat wavelet = Mat::ones(Width, Height, CV_32FC1);
	Mat imgtmp = img.clone();
	imgtmp.convertTo(imgtmp, CV_32FC1);
	while(depthcount <= depth){
		Width = img.rows / depthcount;
		Height = img.cols / depthcount;

		for (int i = 0; i < Width; i++){
			for (int j = 0;j < Height / 2; j++){
				tmp.at<float>(i, j) = (imgtmp.at<float>(i, 2 * j) + imgtmp.at<float>(i, 2 * j + 1)) / 2;
				tmp.at<float>(i, j + Height / 2) = (imgtmp.at<float>(i, 2 * j) - imgtmp.at<float>(i, 2 * j + 1)) / 2;
			}
		}
		imgtmp = wavelet;
		depthcount++;
	}

	namedWindow("jpg", 0);
	wavelet.convertTo(wavelet, CV_8UC1);
	wavelet += 50;
	imshow("jpg", wavelet);
	waitKey(0);
	return 0;
}
