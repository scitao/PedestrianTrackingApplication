#include "TrackingApplicationMainWindow.h"

// Constructors and Destructors
//==================================================
TrackingApplicationMainWindow::TrackingApplicationMainWindow(QWidget *parent) :
QMainWindow(parent),
mainWindowUi(new Ui::TrackingApplicationMainWindow)
{
	// Setup the GUI
	mainWindowUi->setupUi(this);
	this->setWindowTitle("Pedestrain Tracking Application");
	this->setAttribute(Qt::WA_DeleteOnClose, true);

	// Adjust the window based on the resolution of the screen

	// Create a new set of project variables on the heap
	prjVariables =  new ProjectVariables;

	// Show the GUI and block use
	this->show();
	this->setDisabled(true);

	// Make the Main UI fullscreen
	this->showMaximized();

	// Show the welcome dialog
	welcome = new Welcome(this);
	connect(welcome->welcomeDialogUi->loadProjectButton, SIGNAL(clicked()), this, SLOT(loadProject()));
	connect(welcome->welcomeDialogUi->createNewProjectButton, SIGNAL(clicked()), this, SLOT(createNewProject()));
	
	// Connect signals and slots

}

TrackingApplicationMainWindow::~TrackingApplicationMainWindow()
{
	// Delete heap variables
	delete mainWindowUi;
	delete prjVariables;
}

// Public Slots
//==================================================

void TrackingApplicationMainWindow::loadProject()
{
	// If the welcome dialog is open, close and delete
	if (welcome != NULL) welcome->close();

	// If a project is currently loaded, attempt to save it

	// Clear the loaded project variables
	prjVariables->clearProjectVariables();

	// Create a new instance of the project loader

}

void TrackingApplicationMainWindow::createNewProject()
{
	// If the welcome dialog is open, close and delete
	if (welcome != NULL)
	{
		welcome->close();
		delete welcome;
		welcome = NULL;
	}

	// Create a new instance of the new project wizard
	newProjectWizard = new NewProjectWizard(prjVariables, this);
	connect(newProjectWizard, SIGNAL(prematureNewProjectWizardClose()), this, SLOT(showWelcomeDialog()));
	connect(newProjectWizard, SIGNAL(wizardClose()), this, SLOT(nullifyNewProjectWizard()));
	connect(newProjectWizard, SIGNAL(wizardClose()), this, SLOT(enableMainUi()));
	connect(newProjectWizard, SIGNAL(wizardClose()), this, SLOT(saveProject()));
}

void TrackingApplicationMainWindow::saveProject()
{
	// Create a saveSuccessful flag
	bool saveSuccessfulFlag = false;



	// If the save was successful, then reset the projectChangedFlag
	if (saveSuccessfulFlag == true) projectChangedFlag = false;
}

// Public Ui Slots
//==================================================
void TrackingApplicationMainWindow::updateUserInterfaceProjectInformation()
{
	
}

void TrackingApplicationMainWindow::populateMainUiWithProjectInformation()
{
	// Project name
	mainWindowUi->projectNameLineEdit->setText(prjVariables->projectName);

	// Project location
	mainWindowUi->projectLocationLineEdit->setText(prjVariables->projectLocation);

	// Project start date
	mainWindowUi->projectStartDateEdit->setDate(prjVariables->projectStartDate);
}

void TrackingApplicationMainWindow::enableMainUi()
{
	this->setDisabled(false);
}

void TrackingApplicationMainWindow::disableMainUi()
{
	this->setDisabled(true);
}

void TrackingApplicationMainWindow::showWelcomeDialog()
{
	if (welcome == NULL)
	{
		welcome = new Welcome(this);
		connect(welcome->welcomeDialogUi->loadProjectButton, SIGNAL(clicked()), this, SLOT(loadProject()));
		connect(welcome->welcomeDialogUi->createNewProjectButton, SIGNAL(clicked()), this, SLOT(createNewProject()));
		connect(welcome, SIGNAL(welcomeDialogClose()), this, SLOT(nullifyWelcomeDialog()));
	}
	else
	{
		welcome->show();
	}
}

void TrackingApplicationMainWindow::nullifyNewProjectWizard()
{
	newProjectWizard = NULL;
}

void TrackingApplicationMainWindow::nullifyWelcomeDialog()
{
	welcome = NULL;
}