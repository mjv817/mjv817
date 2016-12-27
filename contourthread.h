#ifndef CONTOURTHREAD_H
#define CONTOURTHREAD_H
#include <QThread>
#include <QtWidgets>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



using namespace cv;
//RNG rng(12345);


class ContourThread : public QThread
{

    Q_OBJECT
public:
    explicit ContourThread(QObject * parent = 0);
    void run();
    void thresh_callback(int, void*);


private:
    Mat src;
    Mat src_gray;
    int thresh = 100;
    int max_thresh = 255;






};





#endif // CONTOURTHREAD_H
