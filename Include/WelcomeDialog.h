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
#include <qdialog.h>
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
#include <qmovie.h>

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
#include "ui_WelcomeDialog.h"


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
	class WelcomeDialog;
}

class Welcome : public QDialog
{
	Q_OBJECT

public:
	// Constructors and Destructors
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Welcome(QMainWindow *parent = 0);
	~Welcome();

	// Public Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Public Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Ui::WelcomeDialog* welcomeDialogUi;

	public slots:
	// Public Slots
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


signals:
	void welcomeDialogClose();

private:
	// Private Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	QMovie* logoGif = NULL;

	// Private Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	QRect screenSize;
};