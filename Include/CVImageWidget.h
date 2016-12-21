// Preamble
//==================================================
/*


*/

// Include Guard
//==================================================
#pragma once

// Include Directories
//==================================================
// Qt Directories
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <QWidget>
#include <QImage>
#include <QPainter>

// OpenCV Directories
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <opencv2/opencv.hpp>



class CVImageWidget : public QWidget
{
    Q_OBJECT
	
public:
	// Constructors and Destructors
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    explicit CVImageWidget(QWidget *parent = 0) : QWidget(parent) {}

    QSize sizeHint() const { return _qimage.size(); }
    QSize minimumSizeHint() const { return _qimage.size(); }

public slots:
    
    void showImage(const cv::Mat& image) 
	{
		// Resize the image to fit the window
		QSize widgetSize = this->size();
		cv::Size resizeDimensions(widgetSize.width(), widgetSize.height());
		cv::resize(image, resizedImage, resizeDimensions);

        // Convert the image to the RGB888 format
        switch (resizedImage.type()) {
        case CV_8UC1:
            cvtColor(resizedImage, _tmp, CV_GRAY2RGB);
            break;
        case CV_8UC3:
            cvtColor(resizedImage, _tmp, CV_BGR2RGB);
            break;
        }

        // QImage needs the data to be stored continuously in memory
        assert(_tmp.isContinuous());
        // Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
        // (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
        // has three bytes.
        _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);

        //this->setFixedSize(image.cols, image.rows);

        repaint();
    }

protected:
    void paintEvent(QPaintEvent* /*event*/) 
	{
        // Display the image
        QPainter painter(this);
        painter.drawImage(QPoint(0,0), _qimage);
        painter.end();
    }
    
	cv::Mat resizedImage;
    QImage _qimage;
    cv::Mat _tmp;
};