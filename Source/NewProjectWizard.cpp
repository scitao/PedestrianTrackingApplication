#include "NewProjectWizard.h"

// Constructors and Destructors
//==================================================
NewProjectWizard::NewProjectWizard(ProjectVariables* _prjVariables, QMainWindow *parent) : QDialog(parent), wizardDialog(new Ui::BlankWizard)
{
	// Setup the GUI
	wizardDialog->setupUi(this);
	this->setWindowTitle("New Project Wizard");
	this->setAttribute(Qt::WA_DeleteOnClose, true);

	// Remove the user's ability to close the dialog
	this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

	// Set the variables
	prjVariables = _prjVariables;

	// Call the new page1 method
	newPage1();

	// Show the GUI
	this->show();
}

NewProjectWizard::~NewProjectWizard()
{
	// Delete heap variables
	delete wizardDialog;

	// Emit the wizardClose signal
	emit wizardClose();
}

// Public Slots
//==================================================

void NewProjectWizard::setPage1ProjectVariables()
{
	prjVariables->projectName = page1->page1->projectNameLineEdit->text();
	prjVariables->projectLocation = page1->page1->projectLocationLineEdit->text();
	prjVariables->projectStartDate = page1->page1->projectNameDateEdit->date();
}

void NewProjectWizard::setPage2ProjectVariables()
{

}

void NewProjectWizard::prematureCloseNewProjectWizard()
{
	emit prematureNewProjectWizardClose();
	this->close();
}

void NewProjectWizard::checkPage1()
{
	if (page1->page1->projectNameLineEdit->text().isEmpty())
	{
		page1->page1->projectNameLineEdit->setText("NewProject");
	}
	else if (page1->page1->projectLocationLineEdit->text().isEmpty())
	{
		page1->page1->projectLocationLineEdit->setText("Location");
	}
	else
	{
		newPage2();
	}
}

void NewProjectWizard::addNewCamera()
{
	// Check to see if camera variables have been entered correctly
	if (page2->page2->cameraNameLineEdit->text() == "Camera_Name_Here" || page2->page2->cameraNameLineEdit->text() == "") // ensure a camera name has been entered
	{
		QMessageBox msgBox;
		msgBox.setText("Please enter a valid camera name");
		msgBox.exec();
		return;
	}
	else if (page2->page2->cameraLocationLineEdit->text() == "Camera_Location_Here" || page2->page2->cameraLocationLineEdit->text() == "") // ensure a camera location has been entered
	{
		QMessageBox msgBox;
		msgBox.setText("Please enter a valid camera location description");
		msgBox.exec();
		return;
	}

	// Create a new camera object
	Camera* newCamera = new Camera(page2->page2->cameraNameLineEdit->text(), page2->page2->cameraLocationLineEdit->text());
	newCamera->addVideos(page2->getVideos());

	// Add the camera to the project variables
	prjVariables->cameras.push_back(newCamera);

	// Now create a new add/edit camera dialog
	newPage2();
}

void NewProjectWizard::wizardFinished()
{
	// Attempt to save the latest camera
	if (page2 != NULL)
	{
		// Attempt to save the latest video
		page2->createVideo();

		// Create a new camera object
		Camera* newCamera = new Camera(page2->page2->cameraNameLineEdit->text(), page2->page2->cameraLocationLineEdit->text());
		newCamera->addVideos(page2->getVideos());

		// Add the camera to the project variables
		prjVariables->cameras.push_back(newCamera);

		// Close and nullify page2
		page2->close();
		page2 = NULL;
	}

	// close this wizard
	this->close();
}

// Private Methods
//==================================================

void NewProjectWizard::newPage1()
{
	// If a widget exists in page 1 then close
	if (page1 != NULL )
	{
		page1->close();
	}

	// Set the first wizard page
	page1 = new NewProjectWizardPage1(this);
	wizardDialog->wizardWidget = page1;
	connect(page1->page1->continueButton, SIGNAL(clicked()), this, SLOT(setPage1ProjectVariables()));
	connect(page1->page1->cancelButton, SIGNAL(clicked()), this, SLOT(prematureCloseNewProjectWizard()));
	connect(page1->page1->continueButton, SIGNAL(clicked()), this, SLOT(checkPage1()));

	// Show the GUI
	this->show();
}

void NewProjectWizard::newPage2()
{
	// If a widget exists in page 1 or page 2 then close
	if (page1 != NULL)
	{
		page1->close();
		page1 = NULL;
	}
	if (page2 != NULL)
	{
		page2->close();
		page2 = NULL;
	}

	// Set the first wizard page
	page2 = new NewProjectWizardPage2(this);
	wizardDialog->wizardWidget = page2;
	page2->page2->syncDateTimeEdit->setDate(prjVariables->projectStartDate);
	page2->setStartingDate(prjVariables->projectStartDate);


	// Connect Signals and Slots
	connect(page2->page2->addAnotherCameraButton, SIGNAL(clicked()), this, SLOT(addNewCamera()));
	connect(page2->page2->doneButton, SIGNAL(clicked()), this, SLOT(wizardFinished()));

	// Show the GUI
	this->show();
}