#include "NewProjectWizardPage2.h"

// Constructors and Destructors
//==================================================
NewProjectWizardPage2::NewProjectWizardPage2(QDialog *parent) : QWidget(parent), page2(new Ui::createNewProjectWizardPage2)
{
	// Setup the GUI
	page2->setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose, true);

	// Show the GUI
	this->show();
}

NewProjectWizardPage2::~NewProjectWizardPage2()
{
	// Delete heap variables
	delete page2;
}