#include "WelcomeDialog.h"

// Constructors and Destructors
//==================================================

Welcome::Welcome(QMainWindow *parent) : 
QDialog(parent), welcomeDialogUi(new Ui::WelcomeDialog)
{
	// Setup and show the UI
	welcomeDialogUi->setupUi(this);
	this->setWindowTitle("Welcome");
	this->setAttribute(Qt::WA_DeleteOnClose, true);

	// Adjust the window based on the resolution of the screen
	

	// Show the software logo
	logoGif = new QMovie("LoadingGif3.gif");
	welcomeDialogUi->logoLabel->setMovie(logoGif);
	logoGif->start();

	// Show the Ui
	this->show();

}

Welcome::~Welcome()
{
	// Delete heap variables
	delete welcomeDialogUi;
	delete logoGif;
}