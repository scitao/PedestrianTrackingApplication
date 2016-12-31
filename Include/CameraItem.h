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

#include <QtCore>
#include <qobject.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <qdesktopwidget.h>
#include <qscreen.h>
#include <qsize.h>


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



class CameraItem
{
public:
	// Constructors and Destructors
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CameraItem(const QVector<QVariant> &data, CameraItem* parent = 0);
	~CameraItem();

	// Public Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	CameraItem* child(int number);
	int childCount() const;
	int columnCount() const;
	
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	CameraItem* parent();
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	

	// Public Setters
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bool setData(int column, const QVariant &value);

	// Public Getters
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	QVariant data(int column) const;

	// Public Slots
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
	// Private Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// Private Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	QList<CameraItem*> childItems;
	QVector<QVariant> itemData;
	CameraItem* parentItem;

	// Private Flags
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};