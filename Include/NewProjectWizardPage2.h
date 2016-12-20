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
#include <qmainwindow.h>
#include <qdebug.h>
#include <qobject.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <qapplication.h>
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


// GUI Headers 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "ui_CreateNewProjectWizardPage2.h"

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

namespace Ui
{
	class createNewProjectWizardPage2;
}

class NewProjectWizardPage2 : public QWidget
{
	Q_OBJECT

public:
	// Constructors and Destructors
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	NewProjectWizardPage2(QDialog *parent = 0);
	~NewProjectWizardPage2();

	// Public Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	// Public Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	QRect screenSize;
	Ui::createNewProjectWizardPage2* page2;
	public slots:
	// Public Slots
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// Public Ui Slots
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


signals:

private:
	// Private Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



	// Private Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// Private Flags
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};