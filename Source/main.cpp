// Include Directories
// =============================================================

// Qt
#include <QtCore>
#include <qapplication.h>

// STL
#include <string>
#include <iostream>
#include <exception>

// Windows
#include <Windows.h>

// Program Directories
#include "TrackingApplicationMainWindow.h"

// Namespaces
using namespace std;


int main(int argc, char** argv)
{
	// Create a GUI application
	QApplication app(argc, argv);

	// Set the global style sheet
	QFile f("qdarkstyle/style.qss");
	if (!f.exists())
	{
		printf("Unable to set stylesheet, file not found\n");
	}
	else
	{
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		qApp->setStyleSheet(ts.readAll());
		f.close();
	}

	// Create a new Main Window
	TrackingApplicationMainWindow* mainWindow = new TrackingApplicationMainWindow();
	
	// Print initialisation message to the console
	cout << "\t Pedestrian Tracking Application V 0.1.0 " << endl;
	cout << "\t Created by S.R. Hislop-Lynch " << endl;
	cout << "\t All Rights Reserved" << endl;
	cout << "\t ------------------------------------------------" << endl;

#ifdef NDEBUG
	// Hide the console
	cout << endl << endl;
	cout << "\t >RELEASE MODE -- HIDE CONSOLE" << endl;
	Sleep(200);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

#endif // NDEBUG

#ifdef _DEBUG
	// Clear the console
	Sleep(200);
	system("cls");
#endif // DEBUG

	// Execute
	return(app.exec());
}







