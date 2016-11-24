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
	string fileDirectory = "C:\\Users\\Samue\\Dropbox\\BAC_Project_Sam\\110 - Video Data Collection\\BAC Domestic Terminal Data Collection\\20160915\\Domestic\\Virgin\\";
	string fileName = "BAC_DOMESTIC_VIRGIN_20160915_AUTOMATEDKIOSK2_3of3.MP4";

	// Create descriptor and detection variables
	vector<float> computedDescriptors;
	vector<cv::Point> detections;

	// Create named windows
	cvNamedWindow("Input", CV_WINDOW_KEEPRATIO);
	cvNamedWindow("Features", CV_WINDOW_KEEPRATIO);

	// Loop through the video and show detections
	VideoCapture cap(fileDirectory + fileName);
	Mat frame;
	cap.set(CV_CAP_PROP_POS_FRAMES, 100);

	while (cap.isOpened())
	{
		cap >> frame;
		imshow("Input", frame);
		cv::waitKey(2);

		// Detect
		hog.detect(frame, detections);

		// Show detections
		for (int i = 0; i < detections.size(); i++)
		{
			cv::Rect2i rect(detections.at(i).x, detections.at(i).y, 96, 160);
			cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 1);
		}
		imshow("Features", frame);
		cv::waitKey(500);

		// Calculate corners to be used for detection..

		// Track corners..

	}


	return 0;
}