#include "NewProjectWizard.h"

// Constructors and Destructors
//==================================================
NewProjectWizard::NewProjectWizard(ProjectVariables* _prjVariables, QMainWindow *parent) : QDialog(parent), wizardDialog(new Ui::BlankWizard)
{
	// Setup the GUI
	wizardDialog->setupUi(this);
	this->setWindowTitle("New Project Wizard");
	this->setAttribute(Qt::WA_DeleteOnClose, true);

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
	}
	if (page2 != NULL)
	{
		page2->close();
	}

	// Set the first wizard page
	page2 = new NewProjectWizardPage2(this);
	wizardDialog->wizardWidget = page2;
	page2->page2->syncDateTimeEdit->setDate(prjVariables->projectStartDate);

	// Show the GUI
	this->show();
}