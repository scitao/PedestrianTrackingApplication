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
#include "ProjectVariables.h"
#include "NewProjectWizardPage1.h"
#include "NewProjectWizardPage2.h"
#include "Camera.h"
#include "Video.h"

// GUI Headers 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "ui_EmptyWizardDialog.h"


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
	class EmptyWizard;
}

class NewProjectWizard : public QDialog
{
	Q_OBJECT

public:
	// Constructors and Destructors
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	NewProjectWizard(ProjectVariables* _prjVariables, QMainWindow *parent = 0);
	~NewProjectWizard();

	// Public Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	// Public Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	QRect screenSize;

	public slots:
	// Public Slots
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void setPage1ProjectVariables();
	void setPage2ProjectVariables();
	void prematureCloseNewProjectWizard();
	void wizardFinished();
	void checkPage1();
	void addNewCamera();

	// Public Ui Slots
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


signals:
	void prematureNewProjectWizardClose();
	void wizardClose();

private:
	// Private Methods
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void newPage1();
	void newPage2();


	// Private Variables
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Ui::BlankWizard* wizardDialog;
	NewProjectWizardPage1* page1 = NULL;
	NewProjectWizardPage2* page2 = NULL;
	ProjectVariables* prjVariables = NULL;

	// Private Flags
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};