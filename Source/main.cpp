// Include directories
// ================================================================
#include "HOGTrainerMainWindow.h"

#include <qapplication.h>
#include <qobject.h>
#include <string>
#include <iostream>


#define lInt long int

// Namespaces and definitions
// ================================================================
using std::string;
using std::vector;
using std::list;
using std::ifstream;
using std::iostream;
using std::cout;
using std::endl;

// Main method
// ================================================================
int main(int argc, char** argv)
{
	// Create the event handler
	QApplication app(argc, argv);

	// Print initialisation message to the console
	cout << "\t HOG-SVM Training Application V 0.1.0 " << endl;
	cout << "\t Created by S.R. Hislop-Lynch " << endl;
	cout << "\t All Rights Reserved" << endl;
	cout << "\t ------------------------------------------------" << endl;

	// Create a new instance of the main window
	HOGTrainerMainWindow* mainWindow = new HOGTrainerMainWindow(0);

	return app.exec();
}


/*
void trainSVMClassifier(list<string> positiveImageDirectories, list<string> negativeImageDirectories, string SVMDescriptorfileName, bool leftRightFlipPositiveImages, bool showTraining, string testVideo, Size winSize, Size blockSize, Size cellSize, Size blockStride)
{
	// First Pass training
	// ============================================================
	
	// Create a HOG descriptor object and calibrate with parameters
	HOGDescriptor hog;
	hog.winSize = winSize;
	hog.blockStride = blockStride;
	hog.cellSize = cellSize;
	hog.blockSize = blockSize;
	hog.nbins = 9;

	// Create a display window
	cv::namedWindow("Training");

	// SVM training parameters
	vector<int> labels;
	vector<Mat> gradientVector;
	
	// Image handling variables
	Mat currentImage;
	vector<Point> location;
	vector<float> descriptors;

	// Print to the console
	cout << "\t Calculating training features from positive images...";
	
	// Loop over positive images
	for (list<string>::iterator it = positiveImageDirectories.begin(); it != positiveImageDirectories.end(); it++)
	{
		// Read in an image
		currentImage = imread(*it);

		// If the user has requested, show the training images
		if (showTraining == true)
		{
			imshow("Training", currentImage);
			cv::waitKey(2);
		}

		// Compute the HOG features of the image
		hog.compute(currentImage, descriptors, blockStride, Size(0, 0), location, );

		// Append the gradient vector and labels
		gradientVector.push_back(Mat(descriptors).clone());
		labels.push_back(+1);

		// Perform leftright flip if defined
		if (leftRightFlipPositiveImages == true)
		{
			Mat LRFlip;
			cv::flip(currentImage, LRFlip, 1);

			// Compute the HOG features of the image
			hog.compute(LRFlip, descriptors, blockStride, Size(0, 0), location);

			// Append the gradient vector and labels
			gradientVector.push_back(Mat(descriptors).clone());
			labels.push_back(+1);
		}
	}

	cout << " Done." << endl;

	cout << "\t Calculating training features from negative images..." << endl;

	// Create a random Number generator to extract many features from negative images
	cv::RNG rng;

	// Loop over negative images
	for (list<string>::iterator it = negativeImageDirectories.begin(); it != negativeImageDirectories.end(); it++)
	{
		cout << *it << endl;

		// Read in an image
		currentImage = imread(*it);

		// Check to see if the image has data
		if (currentImage.cols > 0)
		{
			// Extract many features from the negative images
			for (int i = 0; i < 1; i++)
			{
				// Use a random number generator to extract random windows from the negative image set
				
				int imageWidth = currentImage.rows;
				int imageHeight = currentImage.cols;

				int rndX = rng.uniform(0, imageWidth - 2*winSize.width);
				int rndY = rng.uniform(0, imageHeight - 2*winSize.height);
				cv::Rect2i extractionFrameRect(cv::Point2i(rndX, rndY), cv::Point2i(rndX + winSize.width, rndY + winSize.height));

				Mat extractedFrame = Mat(currentImage.clone(), extractionFrameRect);

				// If the user has requested, show the training images
				if (showTraining == true)
				{
					imshow("Training", extractedFrame);
					cv::waitKey(2);
				}

				// Compute the HOG features of the image
				hog.compute(extractedFrame, descriptors, blockStride, Size(0, 0), location);

				// Append the gradient vector and labels
				gradientVector.push_back(Mat(descriptors).clone());
				labels.push_back(-1);
			}
		}
	}

	cout << " Done." << endl;

	cout << "\t Converting data...";

	// Convert the data to a useful format for machine learning
	int rows = (int)gradientVector.size();
	int cols = (int)std::max(gradientVector[0].cols, gradientVector[0].rows);
	Mat tmp(1, cols, CV_32FC1);

	Mat trainData = Mat(rows, cols, CV_32FC1);
	vector<Mat>::const_iterator it = gradientVector.begin();
	vector<Mat>::const_iterator end = gradientVector.end();

	for (int i = 0; it != end; ++it, ++i)
	{
		CV_Assert(it->cols == 1 || it->rows == 1);
		if (it -> cols == 1)
		{
			transpose(*it, tmp);
			tmp.copyTo(trainData.row(i));
		}
		else if (it->rows == 1)
		{
			it->copyTo(trainData.row(i));
		}
	}
	cout << " Done." << endl;

	cout << "\t Training first pass SVM with data...";

	// Create a SVM and set the default values
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
	svm->setCoef0(0.0);
	svm->setDegree(3);
	svm->setTermCriteria(cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, 1e-3));
	svm->setGamma(0);
	svm->setKernel(cv::ml::SVM::LINEAR);
	svm->setNu(0.5);
	svm->setP(0.1);
	svm->setC(0.01);
	svm->setType(cv::ml::SVM::EPS_SVR);

	// Train the SVM
	svm->train(trainData, cv::ml::SampleTypes::ROW_SAMPLE, Mat(labels));

	cout << " Done." << endl;

	// Export the SVM trained data to file
	svm->save("first_pass_detector.yml");

	// Test the first pass detector...

	for (list<string>::iterator it = positiveImageDirectories.begin(); it != positiveImageDirectories.end(); it++)
	{
		// Read in an image
		currentImage = imread(*it);
		vector<Point> foundLocations;

		// detect features
		hog.detect(currentImage, foundLocations);

		for (vector<cv::Point>::iterator it = foundLocations.begin(); it != foundLocations.end(); it++)
		{
			cv::Rect2i rect(*it, Size(80, 80));
			cv::rectangle(currentImage, rect, cv::Scalar(0, 0, 255), 2);
		}

		// If the user has requested, show the training images
		if (showTraining == true)
		{
			imshow("Training", currentImage);
			cv::waitKey(2);
		}


	}


	// Perform Hard training
	// ============================================================
	// Use the trained detector to pass through the 
	// negative image set and retrieve detections
	
	cout << "\t Detecting false positives with negative data set..." << endl;

	// Calibrate the previous HOG detector with the initial SVM results
	hog.setSVMDetector(svm->getSupportVectors());

	// Create a new HOG detector and set variables
	HOGDescriptor hog2;
	hog2.winSize = winSize;
	hog2.blockStride = blockStride;
	hog2.cellSize = cellSize;
	hog2.blockSize = blockSize;
	hog2.nbins = 9;

	lInt falsePositiveCount = 0;


	// Loop through the negative images and compute the HOG features
	// Append the gradient vector and labels with the hard training examples
	for (list<string>::iterator it = negativeImageDirectories.begin(); it != negativeImageDirectories.end(); it++)
	{
		// Read in an image
		currentImage = imread(*it);

		// Print the file name to the console
		cout << *it << endl;

		// Create a container for the false locations
		vector<Point> foundFalsePoints;

		// Detect the features
		hog.detect(currentImage, foundFalsePoints);

		// Print the number of false features found
		cout << "Number of false features found : " << std::to_string(foundFalsePoints.size()) << endl;

		falsePositiveCount += foundFalsePoints.size();

		// If the user has requested, show the training images
		if (showTraining == true)
		{
			for (vector<Point>::iterator iter = foundFalsePoints.begin(); iter != foundFalsePoints.end(); iter++)
			{
				cv::Rect2i rect(*iter, Size(80, 80));
				cv::rectangle(currentImage, rect, cv::Scalar(0, 0, 255), 2);
			}
			
			imshow("Training", currentImage);
			cv::waitKey(2);
		}

		// Append the gradient vector with the false points
		for (vector<Point>::iterator iter = foundFalsePoints.begin(); iter != foundFalsePoints.end(); iter++)
		{
			cv::Rect2i cropWindow(iter->x, iter->y, winSize.width, winSize.height);
			Mat falsePositive(currentImage, cropWindow);

			// Compute the HOG features of the image
			hog.compute(falsePositive, descriptors, blockStride, Size(0, 0), location);

			// Append the gradient vector and labels
			gradientVector.push_back(Mat(descriptors).clone());
			labels.push_back(-1);
		}
	}

	cout << "Total false positives : " << std::to_string(falsePositiveCount) << endl;

	cout << " Done." << endl;

	cout << "\t Converting data...";

	// Convert the data to a useful format for machine learning
	rows = (int)gradientVector.size();
	cols = (int)std::max(gradientVector[0].cols, gradientVector[0].rows);
	Mat tmp2(1, cols, CV_32FC1);

	Mat trainData2 = Mat(rows, cols, CV_32FC1);
	vector<Mat>::const_iterator it2 = gradientVector.begin();
	vector<Mat>::const_iterator end2 = gradientVector.end();

	for (int i = 0; it2 != end2; ++it2, ++i)
	{
		CV_Assert(it2->cols == 1 || it2->rows == 1);
		if (it2->cols == 1)
		{
			transpose(*it2, tmp2);
			tmp2.copyTo(trainData2.row(i));
		}
		else if (it->rows == 1)
		{
			it2->copyTo(trainData2.row(i));
		}
	}

	cout << " Done." << endl;

	cout << "\t Training final hard SVM with false positive data...";







	// Create a new SVM and set the default values
	cv::Ptr<cv::ml::SVM> svmHARD = cv::ml::SVM::create();
	svmHARD->setCoef0(0.0);
	svmHARD->setDegree(3);
	svmHARD->setTermCriteria(cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, 1e-3));
	svmHARD->setGamma(0);
	svmHARD->setKernel(cv::ml::SVM::LINEAR);
	svmHARD->setNu(0.5);
	svmHARD->setP(0.1);
	svmHARD->setC(0.01);
	svmHARD->setType(cv::ml::SVM::EPS_SVR);

	// Train the SVM
	svmHARD->train(trainData2, cv::ml::SampleTypes::ROW_SAMPLE, Mat(labels));

	// Export the SVM trained data to file
	svmHARD->save("hard_detector.yml");


	hog2.setSVMDetector(svmHARD->getSupportVectors());

	cout << " Done." << endl;

	// Test the detector if an inout video has been given 

	if (testVideo == string()) return;

	//cv::VideoCapture cap(testVideo);
	//Mat frame;
	/*
	while (1)
	{
		vector<cv::Point> foundLocations;
		cap >> frame;
		hog2.detect(frame, foundLocations);

		for (vector<cv::Point>::iterator it = foundLocations.begin(); it != foundLocations.end(); it++)
		{
			cv::Rect2i rect(*it, Size(80, 80));
			cv::rectangle(frame, rect, cv::Scalar(0, 0, 255), 2);
		}
		
		// Show image
		imshow("Detections", frame);
		cv::waitKey(20);

	}
	



}
*/

/*
void testSVMClassifier(string videoFileName, string SVMFileLocation)
{
	// Attempt to open the video 
	cv::VideoCapture cap(videoFileName);
	if (!cap.isOpened()) return;

	// Advance the capture beyond the 50th frame
	cap.set(CV_CAP_PROP_POS_FRAMES, 50);

	// Create a new SVM and load the descriptor
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
	svm = cv::ml::SVM::load(SVMFileLocation);
	bool SVMIsClassifier = svm->isClassifier();
	bool SVMIsTrained = svm->isTrained();

	// Create a new HOG detector using the loaded SVM
	Size winSize = Size(80, 80);
	Size blockSize = Size(16, 16);
	Size cellSize = Size(8, 8);
	Size blockStride = Size(8, 8);

	cv::HOGDescriptor hog;
	hog.winSize = winSize;
	hog.blockSize = blockSize;
	hog.blockStride = blockStride;
	hog.cellSize = cellSize;



	Mat supportVectors = svm->getSupportVectors();
	//vector<float> convertedSupportDetectors;

	//int sv_total = supportVectors.rows;
	//Mat alpha, svidx;

	//double rho = svm->getDecisionFunction(0, alpha, svidx);
	//convertedSupportDetectors.resize(supportVectors.cols + 1);
	//memcpy(&convertedSupportDetectors[0], supportVectors.ptr(), supportVectors.cols * sizeof(convertedSupportDetectors[0]));
	//convertedSupportDetectors[supportVectors.cols] = (float)-rho;
	
	//hog.setSVMDetector(convertedSupportDetectors);
	hog.setSVMDetector(supportVectors);


	// Create a new window for showing detections
	cv::namedWindow("Detections", cv::WINDOW_KEEPRATIO);

	// Detect salient features in video stream
	Mat noPeople = imread("C:\\Users\\Samue\\Dropbox\\Sam H-L Only\\University\\MPhil\\260 - Training Images\\INRIAPerson\\Train\\neg\\00000149a.png");
	
	// found locations
	vector<cv::Point> foundLocations;
	hog.detect(noPeople, foundLocations);

	// Draw detection rectangles on video
	for (vector<cv::Point>::iterator it = foundLocations.begin(); it != foundLocations.end(); it++)
	{
		cv::Rect2i rect(*it, Size(80, 80));
		cv::rectangle(noPeople, rect, cv::Scalar(0, 0, 255), 2);
	}

	// Show image
	imshow("Detections", noPeople);
	cv::waitKey(20);

	int i = 0;



	/*
	while (1)
	{
		// Get frame and detect features
		Mat frame;
		cap >> frame;
		vector<cv::Point> foundLocations;
		hog.detect(frame, foundLocations);

		// Draw detection rectangles on video
		for (vector<cv::Point>::iterator it = foundLocations.begin(); it != foundLocations.end(); it++)
		{
			cv::Rect2i rect(*it, Size(80, 80));
			cv::rectangle(frame, rect, cv::Scalar(0,0,255), 2);
		}

		// Show image
		imshow("Detections", frame);
		cv::waitKey(20);

	}
}

*/