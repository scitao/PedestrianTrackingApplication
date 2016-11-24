#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;

int maxCorners = 23;
int maxTrackbar = 450;

RNG rng(12345);
char* source_window = "Image";

/// Function header
void goodFeaturesToTrack_Demo(int, void*);

/**
* @function main
*/
int main(int argc, char** argv)
{
	// Get filepath to video
	string fileDirectory = "C:\\Users\\uqshislo\\Dropbox\\BAC_Project_Sam\\110 - Video Data Collection\\BAC Domestic Terminal Data Collection\\20160915\\Domestic\\Virgin\\";
	string fileName = "BAC_DOMESTIC_VIRGIN_20160915_GANTRY2_3of3.MP4";

	Mat frame;
	vector<Point> features;

	// Loop through the video and show detections
	VideoCapture cap(fileDirectory + fileName);
	cap.set(CV_CAP_PROP_POS_FRAMES, 100);


	while (cap.isOpened())
	{
		cap >> frame;

		// Load source image and convert it to gray
		src = frame;
		cvtColor(src, src_gray, CV_BGR2GRAY);

		// Create Window
		namedWindow(source_window, CV_WINDOW_AUTOSIZE);

		// Create Trackbar to set the number of corners
		createTrackbar("Max  corners:", source_window, &maxCorners, maxTrackbar, goodFeaturesToTrack_Demo);

		imshow(source_window, src);

		goodFeaturesToTrack_Demo(0, 0);

		waitKey(50);

	}


	return(0);
}

/**
* @function goodFeaturesToTrack_Demo.cpp
* @brief Apply Shi-Tomasi corner detector
*/
void goodFeaturesToTrack_Demo(int, void*)
{
	if (maxCorners < 1) { maxCorners = 1; }

	/// Parameters for Shi-Tomasi algorithm
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	/// Copy the source image
	Mat copy;
	copy = src.clone();

	/// Apply corner detection
	goodFeaturesToTrack(src_gray,
		corners,
		maxCorners,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		useHarrisDetector,
		k);


	/// Draw corners detected
	cout << "** Number of corners detected: " << corners.size() << endl;
	int r = 4;
	for (int i = 0; i < corners.size(); i++)
	{
		circle(copy, corners[i], r, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
			rng.uniform(0, 255)), -1, 8, 0);
	}

	/// Show what you got
	namedWindow(source_window, CV_WINDOW_KEEPRATIO);
	imshow(source_window, copy);
}




























/*

// Include directories
// ================================================================
#include <qapplication.h>
#include <qobject.h>

#include <string>
#include <iostream>

#include <opencv2\opencv.hpp>

// Namespaces and definitions
// ================================================================
using std::string;
using std::vector;
using std::list;
using std::ifstream;
using std::iostream;
using std::cout;
using std::endl;

using cv::HOGDescriptor;
using cv::imshow;
using cv::VideoCapture;
using cv::Mat;
using cv::Point;

#define lInt long int



// Main method
// ================================================================
int main(int argc, char** argv)
{

	// Print initialisation message to the console
	cout << "\t Pedestrian Tracking Application V 0.1.0 " << endl;
	cout << "\t Created by S.R. Hislop-Lynch " << endl;
	cout << "\t All Rights Reserved" << endl;
	cout << "\t ------------------------------------------------" << endl;
	

	// Open a new HOG classifier and set the people detector
	HOGDescriptor hog;
	hog.blockSize = cv::Size(16, 16);
	hog.cellSize = cv::Size(8, 8);
	static vector<float> supportVectors = hog.getDefaultPeopleDetector();
	hog.setSVMDetector(supportVectors);
	
	// Get filepath to video
	string fileDirectory = "C:\\Users\\uqshislo\\Dropbox\\BAC_Project_Sam\\110 - Video Data Collection\\BAC Domestic Terminal Data Collection\\20160915\\Domestic\\Virgin\\";
	string fileName = "BAC_DOMESTIC_VIRGIN_20160915_AUTOMATEDKIOSK2_3of3.MP4";

	// Create descriptor and detection variables
	vector<float> computedDescriptors;
	vector<cv::Point> detections;

	// Create named windows
	cvNamedWindow("Input", CV_WINDOW_KEEPRATIO);
	cvNamedWindow("Features", CV_WINDOW_KEEPRATIO);

	// Loop through the video and show detections
	VideoCapture cap(fileDirectory + fileName);
	Mat frame, greyFrameI, greyFrameO;
	vector<Point> features;

	cap.set(CV_CAP_PROP_POS_FRAMES, 100);

	while (cap.isOpened())
	{
		cap >> frame;

		// Detect
		hog.detect(frame, detections);

		// Show detections
		for (int i = 0; i < detections.size(); i++)
		{
			cv::Rect2i rect(detections.at(i).x, detections.at(i).y, 96, 160);
			cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 1);
		}
		imshow("Input", frame);
		cv::waitKey(500);

		// Calculate corners to be used for detection..
		cv::cvtColor(frame, greyFrameI, CV_BGR2GRAY);
		cv::cornerHarris(greyFrameI, greyFrameO, 2, 3, 0.04);

		imshow("Features", greyFrameO);
		cv::waitKey(500);


		// Track corners..

	}


	return 0;
}

*/