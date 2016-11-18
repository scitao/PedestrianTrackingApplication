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
	
	string videoFile = "C:\\Users\\uqshislo\\Dropbox\\BAC_Project_Sam\\110 - Video Data Collection\\BAC Domestic Terminal Data Collection\\20160915\\Domestic\\Virgin\\BAC_DOMESTIC_VIRGIN_20160915_AUTOMATEDKIOSK2_2of3.MP4";

	// Establish a video input stream 
	VideoCapture cap;
	cap.open(videoFile);
	cap.set(CV_CAP_PROP_POS_FRAMES, 100);

	// Open a new HOG classifier
	HOGDescriptor hog;
	const vector<float> peopledetector = hog.getDefaultPeopleDetector();
	hog.setSVMDetector(peopledetector);

	// Create named windows
	cvNamedWindow("Output", CV_WINDOW_KEEPRATIO);
	cvNamedWindow("Features", CV_WINDOW_KEEPRATIO);
	// Loop through the video and show detections
	Mat img, detection, detectionBW;
	vector<Point> foundLocations;
	while (cap.read(img))
	{
		// Detect people
		hog.detect(img, foundLocations);

		// Place bounding boxes around people
		for (int i = 0; i < foundLocations.size(); i++)
		{
			cv::Rect2i rect(foundLocations.at(i).x, foundLocations.at(i).y, hog.winSize.width, hog.winSize.height);
			cv::rectangle(img, rect, cv::Scalar(0, 0, 255));
			imshow("Output", img);
			cv::waitKey(2);

			// Compute good features to track over the found location regions
			vector<cv::Point2f> corners;
			detection = Mat(img, rect).clone();
			detectionBW;
			cv::cvtColor(detection, detectionBW, CV_BGR2GRAY);
			cv::goodFeaturesToTrack(detectionBW, corners, 100, 0.01, 10);

			for (int j = 0; j < corners.size(); j++)
			{
				circle(detection, corners[j], 4, cv::Scalar(0, 255, 0), -1, 8, 0);
				imshow("Features", detection);
				cv::waitKey(2);
			}
		}

		
	}

	return 0;
}