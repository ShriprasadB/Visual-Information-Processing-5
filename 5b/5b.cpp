#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <math.h>

using namespace std;
using namespace cv;

int A[3000][4][4];				// 4x4 blocks of top half of image in M1
int B[3000][4][4];				// 4x4 blocks of bottom half of image in N1

int training_blocks[2400][4][4];
int testing_blocks[2400][4][4];
int no_of_blocks;
//Used for maintaining class information
struct class_info
{
	int label, average;
};

class_info training_info[2400];
class_info testing_info[2400];

void OnMotionvectors(Mat src1, Mat src2)
{
	Mat dst1 = src1.clone();
	Mat dst2 = src2.clone();
	unsigned int difference;
	int avg, temp;

	for (int i = 0; i < dst1.rows; i++)
	{
		for (int j = 0; j < dst1.cols; j++)
		{
			dst1.at<uchar>(i, j) = 0;
		}
	}

	for (int i = 0; i < dst1.rows; i++)
	{
		for (int j = 0; j < dst1.cols; j++)
		{
			dst2.at<uchar>(i, j) = 0;
		}
	}

	for (int m = 0; m < src1.rows; m += 8)
	{
		for (int n = 0; n < src1.cols; n += 8)		//These two loops divide the image into 8x8 blocks
		{
			for (int i = m; i < m + 8; i++)
			{
				for (int j = n; j < n + 8; j++)
				{
					avg = 0, temp = 0;
					for (int x = m; x < m + 8; x++)
					{
						for (int y = n; y < n + 8; y++)
						{
							temp += src1.at<uchar>(x, y);
						}
					}

					avg = temp / 64;

					if (avg < 125)
						avg = 0;
					else if (avg >= 125 && avg < 175)
						avg = 128;
					else if (avg >= 175)
						avg = 255;

					for (int x = m; x < m + 8; x++)
					{
						for (int y = n; y < n + 8; y++)
						{
							dst1.at<uchar>(x, y) = avg;

						}
					}
				}
			}
		}
	}

	for (int m = 0; m < src1.rows; m += 8)
	{
		for (int n = 0; n < src1.cols; n += 8)			//These two loops divide the image into 8x8 blocks
		{
			for (int i = m; i < m + 8; i++)
			{
				for (int j = n; j < n + 8; j++)
				{
					avg = 0, temp = 0;
					for (int x = m; x < m + 8; x++)
					{
						for (int y = n; y < n + 8; y++)
						{
							temp += src2.at<uchar>(x, y);
						}
					}

					avg = temp / 64;

					if (avg < 125)
						avg = 0;
					else if (avg >= 125 && avg < 175)
						avg = 128;
					else if (avg >= 175)
						avg = 255;

					for (int x = m; x < m + 8; x++)
					{
						for (int y = n; y < n + 8; y++)
						{
							dst2.at<uchar>(x, y) = avg;
						}
					}
				}
			}
		}
	}

	//int difference;
	for (int m = 0; m < src1.rows; m += 8)
	{
		for (int n = 0; n < src1.cols; n += 8)			//These two loops divide the image into 8x8 blocks
		{
			for (int i = m; i < m + 8; i++)
			{
				for (int j = n; j < n + 8; j++)
				{
					for (int x = m; x < m + 8; x++)
					{
						for (int y = n; y < n + 8; y++)
						{
							difference = dst1.at<uchar>(x, y) - dst2.at<uchar>(x, y);

						}
					}
				}
			}
		}
	}
/*	namedWindow("SRC1", CV_WINDOW_AUTOSIZE);
	imshow("SRC1", src1);
	namedWindow("SRC2", CV_WINDOW_AUTOSIZE);
	imshow("SRC2", src2);
	namedWindow("DST1", CV_WINDOW_AUTOSIZE);
	imshow("DST1", dst1);
	namedWindow("DST2", CV_WINDOW_AUTOSIZE);
	imshow("DST2", dst2);*/

}

int main(int argc, char *argv[])
{
	Mat src1 = imread(argv[1], 0);
	Mat src2 = imread(argv[2], 0);
	Mat src3;
//	OnMotionvectors(src1, src2);

	if (src1.empty() || src2.empty())
	    {
		cout << "Read error" << endl;
		return -1;
	    }

	    absdiff(src1, src2, src3);
	imshow("difference in two frames", src3);
	waitKey(0);
}
