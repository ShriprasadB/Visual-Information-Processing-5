#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <math.h>

using namespace std;
using namespace cv;

int A[3000][4][4];						//4x4 blocks of top half of image in M1
int B[3000][4][4];						//4x4 blocks of bottom half of image in N1

int training_blocks[2400][4][4];
int testing_blocks[2400][4][4];
int no_of_blocks;
//to maintain class information
struct class_info
{
	int label, average;
};

class_info training_info[2400];
class_info testing_info[2400];

//to generate M1 image
Mat GenerateM1(Mat src)
{
	int temp;
	int height = src.rows - (src.rows % 4);
	int ht = src.rows;
	int wt = src.cols;
	int width = src.cols - (src.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat dst = src.clone();
	for (int m = 0; m < height / 2; m += 4)
	{
		for (int n = 0; n < width; n += 4)		//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							temp += src.at<uchar>(x, y);
						}
					}
					avg = temp / 16;
					training_info[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						training_info[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						training_info[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						training_info[p].label = label;
					}

					training_info[p].label = label;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							dst.at<uchar>(x, y) = label;

						}
					}

				}
			}
			p++;
		}
	}
	return dst;
}

Mat GenerateT1(Mat src)
{
	int temp;
	int height = src.rows - (src.rows % 4);
	int ht = src.rows;
	int wt = src.cols;
	int width = src.cols - (src.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat dst = src.clone();
	for (int m = src.rows / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)		//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							temp += src.at<uchar>(x, y);
						}
					}
					avg = temp / 16;
					testing_info[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						testing_info[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						testing_info[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						testing_info[p].label = label;
					}

					testing_info[p].label = label;
					for (int x = m; x < m + 4; x++)
					{
						for (int y = n; y < n + 4; y++)
						{
							dst.at<uchar>(x, y) = label;

						}
					}

				}
			}
			p++;
		}
	}
	namedWindow("T1", CV_WINDOW_AUTOSIZE);
	imshow("T1", dst);
	return dst;
	
}

void ObtainTopBlocks(Mat src, int A[2400][4][4])
{
	int temp;
	int height = src.rows - (src.rows % 4);
	int ht = src.rows;
	int wt = src.cols;
	int x1, y1;
	int width = src.cols - (src.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat dst = src.clone();
	for (int m = 0; m < height / 2; m += 4)
	{
		for (int n = 0; n < width; n += 4)		//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0, x1 = 0;
					for (int x = m; x < m + 4; x++)
					{
						y1 = 0;
						for (int y = n; y < n + 4; y++)
						{
							A[p][x1][y1] = src.at<uchar>(x, y);
							y1++;
							temp += src.at<uchar>(x, y);
						}
						x1++;
					}
					avg = temp / 16;
					training_info[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						training_info[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						training_info[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						training_info[p].label = label;
					}

					training_info[p].label = label;
				}
			}
			p++;
		}
	}
	
}

void ObtainBottomBlocks(Mat src, int A[2400][4][4])
{
	int temp;
	int height = src.rows - (src.rows % 4);
	int ht = src.rows;
	int wt = src.cols;
	int x1, y1;
	int width = src.cols - (src.cols % 4);
	int sum, avg, label;
	int p = 0;
	Mat dst = src.clone();
	for (int m = src.rows / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)		//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					avg = 0, temp = 0, x1 = 0;
					for (int x = m; x < m + 4; x++)
					{
						y1 = 0;
						for (int y = n; y < n + 4; y++)
						{
							A[p][x1][y1] = src.at<uchar>(x, y);
							y1++;
							temp += src.at<uchar>(x, y);
						}
						x1++;
					}
					avg = temp / 16;
					testing_info[p].average = avg;

					if (avg < 125)
					{
						label = 0;
						testing_info[p].label = label;
					}
					else if (avg >= 125 && avg < 175)
					{
						label = 128;
						testing_info[p].label = label;
					}
					else if (avg >= 175)
					{
						label = 255;
						testing_info[p].label = label;
					}

					testing_info[p].label = label;
				}
			}
			p++;
		}
	}
	

}

Mat GenerateN1(Mat src, int A[2400][4][4], int B[2400][4][4], int no_of_blocks)
{
	Mat dst = src.clone();
	int mean, avg, temp, sum, classID, p;

	for (int i = 0; i < no_of_blocks; i++)
	{
		mean = 128;
		for (int j = 0; j < no_of_blocks; j++)
		{
			avg = 0, temp = 0;
			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					temp += pow(A[j][k][l] - B[i][k][l], 2);
				}
			}
			sum = sqrt(temp);
			avg = sum / 16;
			if (avg < mean)
			{
				mean = avg;
				classID = j;
			}

		}
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				B[i][x][y] = A[classID][x][y];		//to Set class label to bottom half
			}
		}
	}

	int xx, yy;
	int height = src.rows - (src.rows % 4);
	int width = src.cols - (src.cols % 4);

	p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)		//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							dst.at<uchar>(x, y) = B[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}
	return dst;
}

Mat GenerateN2(Mat src, int A[2400][4][4], int B[2400][4][4], int no_of_blocks)
{
	Mat dst = src.clone();
	int classID = 0, count = 0;
	unsigned int distance, new_distance = 255;
	for (int i = 0; i < no_of_blocks; i++)
	{
		distance = 255;
		for (int j = 0; j < no_of_blocks; j++)
		{
			new_distance = 255;
			new_distance = training_info[j].average - testing_info[i].average;
			if (new_distance < distance)
			{
				distance = new_distance;
				classID = j;
			}

		}

		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				B[i][k][l] = A[classID][k][l];
				
			}
		}
	}

	int height = src.rows - (src.rows % 4);
	int width = src.cols - (src.cols % 4);
	int xx, yy;
	int p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)			//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							dst.at<uchar>(x, y) = B[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}

	return dst;
}

Mat GenerateN3(Mat src, int A[2400][4][4], int B[2400][4][4], int no_of_blocks)
{
	Mat dst = src.clone();
	int classID = 0, count = 0;
	unsigned int distance, new_distance = 255;
	for (int i = 0; i < no_of_blocks; i++)
	{
		distance = 255;
		for (int j = 0; j < no_of_blocks; j++)
		{
			new_distance = 255;
			new_distance = training_info[j].average - testing_info[i].average;
			if (new_distance < distance)
			{
				distance = new_distance;
				classID = j;
			}

		}

		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				B[i][k][l] = training_info[classID].average;
				
			}
		}
	}

	int height = src.rows - (src.rows % 4);
	int width = src.cols - (src.cols % 4);
	int xx, yy;
	int p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)			//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							dst.at<uchar>(x, y) = B[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}

	return dst;
}

int getAverageOfClasses(int matching_label)
{
	int i = 0;
	int temp = 0, avg;
	while (i < 2400)
	{
		if (training_info[i].label == matching_label)
		{
			temp += training_info[i].average;
		}
		i++;
	}
	avg = temp / i;
	return avg;
}

Mat GenerateN4(Mat src, int A[2400][4][4], int B[2400][4][4], int no_of_blocks)
{
	Mat dst = src.clone();
	int classID = 0, count = 0, matching_label, cumulative_avg;
	unsigned int distance, new_distance = 255;
	for (int i = 0; i < no_of_blocks; i++)
	{
		distance = 255;
		for (int j = 0; j < no_of_blocks; j++)
		{
			new_distance = 255;
			new_distance = training_info[j].average - testing_info[i].average;
			if (new_distance < distance)
			{
				distance = new_distance;
				classID = j;
			}

		}

		matching_label = training_info[classID].label;
		cumulative_avg = getAverageOfClasses(matching_label);

		for (int k = 0; k < 4; k++)
		{
			for (int l = 0; l < 4; l++)
			{
				B[i][k][l] = cumulative_avg;
			}
		}
	}

	int height = src.rows - (src.rows % 4);
	int width = src.cols - (src.cols % 4);
	int xx, yy;
	int p = 0;
	for (int m = height / 2; m < height; m += 4)
	{
		for (int n = 0; n < width; n += 4)			//These two loops divide the image into 4x4 blocks
		{
			for (int i = m; i < m + 4; i++)
			{
				for (int j = n; j < n + 4; j++)
				{
					xx = 0;
					for (int x = m; x < m + 4; x++)
					{
						yy = 0;
						for (int y = n; y < n + 4; y++)
						{
							dst.at<uchar>(x, y) = B[p][xx][yy];
						}
					}
				}
			}
			p++;
		}
	}

	return dst;
}


void OnDivide()										
{
	
	Mat src = imread("E:\\Assignment 4 images\\TestImage-even-width.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat M1 = src.clone();
	int temp;
	int height = src.rows - (src.rows % 4);
	int ht = src.rows;
	int wt = src.cols;
	int width = src.cols - (src.cols % 4);
	int sum, avg;

	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", src);

	//to obtain image M1
	M1 = GenerateM1(src);

	namedWindow("M1", CV_WINDOW_AUTOSIZE);
	imshow("M1", M1);

	ObtainTopBlocks(M1, training_blocks);
	ObtainBottomBlocks(M1, testing_blocks);

	no_of_blocks = ((src.rows / 2) / 4) * (src.cols / 4);
	int mean, output = 0, classID, j, p;
	unsigned temp1, sum1;
	Mat N1 = M1.clone();
	//to Generate image N1
	N1 = GenerateN1(M1, training_blocks, testing_blocks, no_of_blocks);
	namedWindow("N1", CV_WINDOW_AUTOSIZE);
	imshow("N1", N1);



	//to Generate image N3
	ObtainTopBlocks(src, training_blocks);
	ObtainBottomBlocks(src, testing_blocks);
	Mat N3 = M1.clone();
	N3 = GenerateN3(src, training_blocks, testing_blocks, no_of_blocks);
	namedWindow("N3", CV_WINDOW_AUTOSIZE);
	imshow("N3", N3);

	//to Generate image N4
	ObtainTopBlocks(src, training_blocks);
	ObtainBottomBlocks(src, testing_blocks);
	Mat N4 = M1.clone();
	N4 = GenerateN4(src, training_blocks, testing_blocks, no_of_blocks);
	namedWindow("N4", CV_WINDOW_AUTOSIZE);
	imshow("N4", N4);

	float no_of_different_averages = 0;
	float no_of_same_averages = 0;
	float no_of_different_labels = 0;
	float no_of_same_labels = 0;

	float error_rate = 0;
	for (int i = 0; i < no_of_blocks; i++)
	{

		if (training_info[i].average != testing_info[i].average)
			no_of_different_averages++;
		else if (training_info[i].average == testing_info[i].average)
			no_of_same_averages++;

		if (training_info[i].label != testing_info[i].label)
			no_of_different_labels++;
		else if (training_info[i].label == testing_info[i].label)
			no_of_same_labels++;

	}
	error_rate = (no_of_different_labels / no_of_blocks) * 100;
	cout << error_rate << endl;

	

	
}





int main(int argc, char *argv[])
{
	Mat src = imread(argv[1], 0);


	Mat M1 = src.clone();
	M1 = GenerateM1(src);
	namedWindow("M1", CV_WINDOW_AUTOSIZE);
	imshow("M1", M1);
	
	no_of_blocks = ((src.rows / 2) / 4) * (src.cols / 4);
	//to Generate image N1
	ObtainTopBlocks(M1, training_blocks);
	ObtainBottomBlocks(M1, testing_blocks);
	Mat N1 = src.clone();
	N1 = GenerateN1(M1, training_blocks, testing_blocks, no_of_blocks);

	namedWindow("N1", CV_WINDOW_AUTOSIZE);
	imshow("N1", N1);
	float errorrate = 0;
	float no_of_different_averages = 0;
	float no_of_same_averages = 0;
	float no_of_different_labels = 0;
	float no_of_same_labels = 0;
	for (int i = 0; i < no_of_blocks; i++)
	{

		if (training_info[i].average != testing_info[i].average)
			no_of_different_averages++;
		else if (training_info[i].average == testing_info[i].average)
			no_of_same_averages++;

		if (training_info[i].label != testing_info[i].label)
			no_of_different_labels++;
		else if (training_info[i].label == testing_info[i].label)
			no_of_same_labels++;

	}

	
	
	errorrate = (no_of_different_labels / no_of_blocks) * 100;
	cout <<"Error Rate:"<< errorrate << endl;




	no_of_blocks = ((src.rows / 2) / 4) * (src.cols / 4);
	
	//to Generate image N2
	ObtainTopBlocks(src, training_blocks);
	ObtainBottomBlocks(src, testing_blocks);
	Mat N2 = src.clone();
	N2 = GenerateN2(src, training_blocks, testing_blocks, no_of_blocks);

	namedWindow("N2", CV_WINDOW_AUTOSIZE);
	imshow("N2", N2);


	no_of_blocks = ((src.rows / 2) / 4) * (src.cols / 4);

	//to Generate image N3
	ObtainTopBlocks(src, training_blocks);
	ObtainBottomBlocks(src, testing_blocks);
	Mat N3 = src.clone();
	N3 = GenerateN3(src, training_blocks, testing_blocks, no_of_blocks);

	namedWindow("N3", CV_WINDOW_AUTOSIZE);
	imshow("N3", N3);

	GenerateT1(src);
//	Kmeans
	Mat dst = src.clone();
	int height = src.rows;
	int width = src.cols;

	for ( int i = 0; i < height/2; i++ )
	{
	for ( int j = 0; j < width; j++ )
	{
	if ( src.at<uchar>(i, j) > 0 && src.at<uchar>(i, j) <= 85 )
	dst.at<uchar>(i, j) = 0;
	else if ( src.at<uchar>(i, j) > 85 && src.at<uchar>(i, j) <= 170 )
	dst.at<uchar>(i, j) = 128;
	else if( src.at<uchar>(i, j) > 170 && src.at<uchar>(i, j) <= 255 )
	dst.at<uchar>(i, j) = 255;
	}
	}

	namedWindow("K-means", CV_WINDOW_AUTOSIZE);
	imshow("K-means", dst);


	no_of_blocks = ((src.rows / 2) / 4) * (src.cols / 4);
	//to Generate image N4
	ObtainTopBlocks(src, training_blocks);
	ObtainBottomBlocks(src, testing_blocks);
	Mat N4 = src.clone();
	N4 = GenerateN4(src, training_blocks, testing_blocks, no_of_blocks);

	namedWindow("N4", CV_WINDOW_AUTOSIZE);
	imshow("N4", N4);
	
	
	
	
	waitKey();
	getchar();
}
