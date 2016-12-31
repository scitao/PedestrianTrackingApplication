#include "Camera.h"

// Constructors and Destructors
//==================================================
Camera::Camera(QString _name, QString _locationDescription, QObject *parent) : QObject(parent)
{
	// Populate the private variables
	cameraName = _name;
	cameraLocationDescription = _locationDescription;
}

Camera::~Camera()
{
	// Destructor
}

// Public Setters
//==================================================
void Camera::addVideo(Video* _video)
{
	videoList.append(_video);
}

void Camera::addVideos(QList<Video*> _videos)
{
	videoList += _videos;
}

void Camera::setCameraName(QString _name)
{
	cameraName = _name;
}

void Camera::setCameraLocationDescription(QString _locationDescription)
{
	cameraLocationDescription = _locationDescription;
}

// Public Getters
//==================================================
QList<Video*> Camera::getVideos()
{
	return videoList;
}

QString Camera::getCameraName()
{
	return cameraName;
}

QString Camera::getCameraLocationDescription()
{
	return cameraLocationDescription;
}

CameraItem* Camera::getCameraItem()
{
	return cameraItem;
}