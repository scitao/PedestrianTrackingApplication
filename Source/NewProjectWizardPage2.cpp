#include "NewProjectWizardPage2.h"

// Constructors and Destructors
//==================================================
NewProjectWizardPage2::NewProjectWizardPage2(QDialog *parent) : QWidget(parent), page2(new Ui::createNewProjectWizardPage2)
{
	// Setup the GUI
	page2->setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose, true);
	

	// Connect signals and slots
	connect(page2->currentFrameSpinBox, SIGNAL(editingFinished()), this, SLOT(frameSpinBoxChanged()));
	connect(page2->videoPositionSlider, SIGNAL(sliderReleased()), this, SLOT(sliderChanged()));
	connect(page2->PreviousFrameButton, SIGNAL(clicked()), this, SLOT(previousFrame()));
	connect(page2->nextFrameButton, SIGNAL(clicked()), this, SLOT(nextFrame()));
	connect(page2->browseForVideoFileButton, SIGNAL(clicked()), this, SLOT(browseForVideoFile()));
	connect(page2->addAnotherVideoFileButton, SIGNAL(clicked()), this, SLOT(addAnotherVideo()));


	// Show the GUI
	this->repaint();
	this->show();
}

NewProjectWizardPage2::~NewProjectWizardPage2()
{
	// Delete heap variables
	delete page2;

}


// Public Getters
//==================================================
QList<Video*> NewProjectWizardPage2::getVideos()
{
	return videos;
}


// Public Setters
//==================================================
void NewProjectWizardPage2::setStartingDate(QDate _startingDate)
{
	startDate = _startingDate;
}

// Public Slots
//==================================================
void NewProjectWizardPage2::browseForVideoFile()
{
	
	// Open a File IO dialog and get user to select video
	QString videoFileName = QFileDialog::getOpenFileName(this, tr("Open Video File"),
		"C:/",
		tr("Video Files (*.mov *.mp4 *.avi *.wmv *.mpeg)"));

	// If the video is valid continue
	if (videoFileName.isEmpty()) return;

	// Keep the video file as a variable
	currentVideoFileName = videoFileName;

	// If a video file stream is already open, close it
	if (cap.isOpened()) cap.release();

	// Open the video file and show first frame
	cap.open(currentVideoFileName.toStdString());

	// Update the video slider and current frame spin box maximums
	page2->videoPositionSlider->setMaximum(cap.get(CV_CAP_PROP_FRAME_COUNT) - 1);
	page2->currentFrameSpinBox->setMaximum(cap.get(CV_CAP_PROP_FRAME_COUNT) - 1);
	
	// Update the file name label
	page2->videoFileNameLabel->setText(currentVideoFileName);

	// Reset the sync time DateTimeEditBox
	page2->syncDateTimeEdit->setDate(startDate);

	// Render the 0th video frame
	renderVideoFrame(0);
}

void NewProjectWizardPage2::renderVideoFrame(lInt frameNumber)
{
	// Check to make sure a capture stream is opened, otherwise do nothing
	if (!cap.isOpened()) return;

	// Set the nextframe to be decoded
	cap.set(CV_CAP_PROP_POS_FRAMES, frameNumber);

	// Push the frame to the currentImage container
	cap >> currentImage;

	// Render the video frame to the GUI
	page2->videoWidget->showImage(currentImage);

	// Update the GUI slider
	if (page2->videoPositionSlider->sliderPosition() != frameNumber)
	{
		page2->videoPositionSlider->setSliderPosition(frameNumber);
	}

	// Update the current frame spin box 
	if (page2->currentFrameSpinBox->value() != frameNumber)
	{
		page2->currentFrameSpinBox->setValue(frameNumber);
	}
	
}

void NewProjectWizardPage2::previousFrame()
{
	// Check to make sure a capture stream is opened, otherwise do nothing
	if (!cap.isOpened()) return;

	// Check to make sure the video stream position isn't 0, otherwise do nothing
	if (cap.get(CV_CAP_PROP_POS_FRAMES) - 1 < 0) return;

	// Render the previous frame
	lInt frameToRender = cap.get(CV_CAP_PROP_POS_FRAMES) - 2;
	renderVideoFrame(frameToRender);
}

void NewProjectWizardPage2::nextFrame()
{
	// Check to make sure a capture stream is opened, otherwise do nothing
	if (!cap.isOpened()) return;

	// Check to make sure the video stream position isn't at end, otherwise do nothing
	if (cap.get(CV_CAP_PROP_POS_FRAMES) + 1 > cap.get(CV_CAP_PROP_FRAME_COUNT) - 1 ) return;

	// Render the next frame
	lInt frameToRender = cap.get(CV_CAP_PROP_POS_FRAMES);
	renderVideoFrame(frameToRender);
}

void NewProjectWizardPage2::sliderChanged()
{
	// Check to make sure a capture stream is opened, otherwise do nothing
	if (!cap.isOpened()) return;
	
	// Get the slider position
	lInt frameToRender = page2->videoPositionSlider->sliderPosition();

	// Render the video frame
	renderVideoFrame(frameToRender);
}

void NewProjectWizardPage2::frameSpinBoxChanged()
{
	// Check to make sure a capture stream is opened, otherwise do nothing
	if (!cap.isOpened()) return;

	// Get the frameSpinBox position 
	lInt frameToRender = page2->currentFrameSpinBox->value();
	
	// Render the video frame
	renderVideoFrame(frameToRender);
}

void NewProjectWizardPage2::addAnotherVideo()
{
	// First, check to see if the current video has been initialised. If not show warning and return
	if (currentVideoFileName.isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText("Current video file not initialised!");
		msgBox.exec();

		return;
	}

	// Create a new video container for the current video
	createVideo();

	// Reset the GUI containers and repaint the videoPlayer black
	currentVideoFileName = QString();
	cap.release();
	page2->videoFileNameLabel->setText("No Video File Selected!");
	page2->syncDateTimeEdit->setDate(startDate);
	currentImage = Mat::zeros(100, 100, CV_8UC3);
	page2->videoWidget->showImage(currentImage);

}

// Private Methods
//==================================================
void NewProjectWizardPage2::createVideo()
{
	// Check to make sure a capture stream is opened, otherwise do nothing
	if (!cap.isOpened()) return;

	// Get the details of the video file and create a new container
	Video* newVideoContainer = new Video;
	newVideoContainer->setNumberOfFrames(cap.get(CV_CAP_PROP_FRAME_COUNT));
	newVideoContainer->setVideoDirectory(currentVideoFileName);


	// Calculate and set the sync time
	QDateTime syncStartingTime = page2->syncDateTimeEdit->dateTime().addMSecs(-cap.get(CV_CAP_PROP_POS_MSEC));
	newVideoContainer->setSyncStartTime(syncStartingTime);

	// Get the filename and extension without the directory
	newVideoContainer->setVideoFileName(getVideoFileNameOnly());

	// Push the newly created video to the back of hte videos container
	videos.push_back(newVideoContainer);

	// Add the video file name to the back of the GUI video file list
	page2->videoFileListWidget->addItem(getVideoFileNameOnly());

}

QString NewProjectWizardPage2::getVideoFileNameOnly()
{
	// Check to make sure a capture stream is opened, otherwise do nothing
	if (!cap.isOpened()) return QString();

	// Retrieve the filename and extension
	QString fileNameOnly;
	int stringPostion = currentVideoFileName.size() - 1;
	while (currentVideoFileName.at(stringPostion) != QString("/") && stringPostion > 0)
	{
		fileNameOnly.push_front(currentVideoFileName.at(stringPostion));
		stringPostion--;
	}

	// Return the result
	return fileNameOnly;
}
