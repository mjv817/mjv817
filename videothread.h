#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H
#include <QThread>
#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>



class QImage;

using namespace cv;


class VideoThread : public QThread
{

    Q_OBJECT

public:
    explicit VideoThread(QObject *parent = 0);
    void run();
    bool doCapture = false;
    bool processFrame(const cv::Mat &imageIn, cv::Mat &imageOut);

private:
    QImage convertMat(const cv::Mat &inMat);
    void thresh_callback(int, void*);
    Mat src;
    Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;




signals:
    void FrameChanged(const cv::Mat &frame);
    void ConvertedFrameChanged(QImage);


public slots:






};









#endif // VIDEOTHREAD_H
