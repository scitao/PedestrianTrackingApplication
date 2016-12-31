#include "Video.h"

// Setters
//==================================================
void Video::setVideoDirectory(QString _videoDirectory)
{
	videoDirectory = _videoDirectory;
}

void Video::setSyncStartTime(QDateTime _syncStartTime)
{
	syncStartTime = _syncStartTime;
}

void Video::setNumberOfFrames(lInt _numberOfFrames)
{
	numberOfFrames = _numberOfFrames;
}

void Video::setVideoFileName(QString _videoFileName)
{
	videoFileName = _videoFileName;
}

void Video::setCameraItem(CameraItem* _cameraItem)
{
	cameraItem = _cameraItem;
}

// Getters
//==================================================
QString Video::getVideoDirectory()
{
	return videoDirectory;
}

QDateTime Video::getSyncStartTime()
{
	return syncStartTime;
}

lInt Video::getNumberOfFrames()
{
	return numberOfFrames;
}

QString Video::getVideoFileName()
{
	return videoFileName;
}

CameraItem* Video::getCameraItem()
{
	return cameraItem;
}