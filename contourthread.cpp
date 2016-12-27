#include "mythread.h"
#include "videothread.h"
#include "contourthread.h"
#include <QtCore>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;



ContourThread::ContourThread(QObject *parent) : QThread(parent)
{

}

void ContourThread::run()
{

    src = imread("/home/mjv817/QTProjects/openContour/shapes.jpg");

    cvtColor(src,src_gray,CV_BGR2GRAY);
    blur(src_gray,src_gray,Size(3,3) );

    namedWindow("Source", CV_WINDOW_NORMAL);
    imshow("Source", src);







}


void ContourThread::thresh_callback(int, void *)
{

    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;













}

