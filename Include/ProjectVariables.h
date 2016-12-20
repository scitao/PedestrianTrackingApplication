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

// OpenCV Directories
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <opencv2\opencv.hpp>


// STL
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <string>
#include <list>
#include <vector>


// Program Directories
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// GUI Headers 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "ui_TrackingApplicationMainWindowUI.h"
#include "ui_CreateNewProjectWizardPage1.h"
#include "ui_CreateNewProjectWizardPage2.h"

// Namespaces
//==================================================
using std::string;
using std::list;
using std::vector;

// Struct Definition
//==================================================

struct ProjectVariables
{
	// Variables
	QString projectName;
	QString projectLocation;
	QDate projectStartDate;
	QString saveFileName;

	// Methods
	void clearProjectVariables()
	{
		projectName = QString();
		projectLocation = QString();
		projectStartDate = QDate();
		saveFileName = QString();
	}

};