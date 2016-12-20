#include "NewProjectWizardPage1.h"

// Constructors and Destructors
//==================================================
NewProjectWizardPage1::NewProjectWizardPage1(QDialog *parent) : QWidget(parent), page1(new Ui::createNewProjectWizardPage1)
{
	// Setup the GUI
	page1->setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose, true);

	// Show the GUI
	this->show();
}

NewProjectWizardPage1::~NewProjectWizardPage1()
{
	// Delete heap variables
	delete page1;
}