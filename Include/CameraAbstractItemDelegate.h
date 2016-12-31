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
#include <qabstractitemdelegate.h>

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
#include "Video.h"

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

// Class Declaration
//==================================================



class CameraAbstractItemDelegate : public QAbstractItemDelegate
{
	Q_OBJECT

public:
	// Constructors and Destructors
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CameraAbstractItemDelegate(QString _name, QString _locationDescription, QObject *parent = 0);
	~CameraAbstractItemDelegate();

	// Public Setters
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Public Getters
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Public Slots
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
	// Private Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// Private Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// Private Flags
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};