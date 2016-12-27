#include "mythread.h"
#include "videothread.h"
#include <QtCore>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
class QImage;

RNG rng(12345);

VideoThread::VideoThread(QObject *parent) : QThread(parent)
{

}

bool VideoThread::processFrame(const cv::Mat &imageIn, cv::Mat &imageOut)
{
    imageIn.copyTo(imageOut);
    return true;

}

QImage VideoThread::convertMat(const Mat &inMat)
{

    switch ( inMat.type() )
    {
       // 8-bit, 4 channel
       case CV_8UC4:
       {
          QImage image( inMat.data,
                        inMat.cols, inMat.rows,
                        static_cast<int>(inMat.step),
                        QImage::Format_ARGB32 );

          return image;
       }

       // 8-bit, 3 channel
       case CV_8UC3:
       {
          QImage image( inMat.data,
                        inMat.cols, inMat.rows,
                        static_cast<int>(inMat.step),
                        QImage::Format_RGB888 );

          return image.rgbSwapped();
       }

       // 8-bit, 1 channel
       case CV_8UC1:
       {
          static QVector<QRgb>  sColorTable( 256 );

          // only create our color table the first time
          if ( sColorTable.isEmpty() )
          {
             for ( int i = 0; i < 256; ++i )
             {
                sColorTable[i] = qRgb( i, i, i );
             }
          }

          QImage image( inMat.data,
                        inMat.cols, inMat.rows,
                        static_cast<int>(inMat.step),
                        QImage::Format_Indexed8 );

          image.setColorTable( sColorTable );

          return image;
       }

       default:
          qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
          break;
    }


    return QImage();

}

void VideoThread::run()
{


    Mat frame;
    VideoCapture cap;
    QImage convertedFrame;
    //int i;


    cap.open(0);
    if(!cap.isOpened())
    {
        cout << "ERROR! Unable to open camera\n";
    }

    cout << "Start Grabbing!" << endl;


    QMutex mutex;
    while(doCapture)
    {
        mutex.lock();
        Mat captureFrame;
        Mat processedFrame;




        bool captureSuccess = cap.read(captureFrame);
        if(captureSuccess)
        {
            processFrame(captureFrame, processedFrame);
            convertedFrame = convertMat(processedFrame);
            cvtColor(processedFrame, src_gray, CV_BGR2GRAY);
            blur(src_gray,src_gray,Size(3,3));
        }
        else
        {
            printf("Unable to acquire image from frame!\n");
        }


        if(captureSuccess)
        {
            //cv::imshow("Webcam Stream", processedFrame);
            //emit FrameChanged(processedFrame);
            emit ConvertedFrameChanged(convertedFrame);
            thresh_callback(0,0);

        }
        mutex.unlock();




    }


}

void VideoThread::thresh_callback(int, void *)
{
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    threshold(src_gray,threshold_output,thresh,255,THRESH_BINARY);

    findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE,Point(0,0));

    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f>center(contours.size());
    vector<float>radius(contours.size());

    //cout << "Contour Size: %f: " << contours.size() << endl;


    for(int i = 0; i < contours.size(); i++)
    {
        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = boundingRect(Mat(contours_poly[i]));
        minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );

    }

    /// Draw polygonal contour + bonding rects + circles
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
       {
         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
         drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
         rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
         //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
       }

    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );



}
