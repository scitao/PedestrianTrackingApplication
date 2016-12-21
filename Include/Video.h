// Preamble
//==================================================
/*


*/

// Include Guard
//==================================================
#pragma once

// Include Directories
//==================================================
// Qt Directories
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <qobject.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <qdesktopwidget.h>
#include <qscreen.h>
#include <qsize.h>
#include <qdatetime.h>

// OpenCV Directories
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <opencv2\opencv.hpp>


// STL
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <math.h>

// Program Directories
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// GUI Headers 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// Namespaces
//==================================================
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::list;
using std::vector;

using cv::Size;
using cv::Mat;
using cv::namedWindow;
using cv::imshow;

// Definitions
//==================================================

#define lInt long int

// Struct Declaration
//==================================================

struct Video
{
public:
	// Setters
	void setVideoDirectory(QString _videoDirectory);
	void setSyncStartTime(QDateTime _syncStartTime);
	void setNumberOfFrames(lInt _numberOfFrames);
	void setVideoFileName(QString _videoFileName);

	// Getters
	QString getVideoFileName();
	QString getVideoDirectory();
	QDateTime getSyncStartTime();
	lInt getNumberOfFrames();

private:
	QString videoFileName;
	QString videoDirectory;
	QDateTime syncStartTime;
	lInt numberOfFrames;
};
