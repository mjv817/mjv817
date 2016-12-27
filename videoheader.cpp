#include <QtWidgets>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "videoheader.h"
//#include "mainwindow.h"
using namespace cv;
using namespace std;

VideoHeader::VideoHeader()
{
    createCapture();
}


QImage VideoHeader::convertMat(const cv::Mat &inMat)
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


void VideoHeader::createCapture()
{

    Mat frame;
    VideoCapture cap;
    QImage convertedFrame;
    int i;


    cap.open(0);
    if(!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
    }

    cout << "Start grabbing" << endl;




    for(;;)
    {
        QMutex mutex;
        mutex.lock();
        cout << "Reading Frame Next Line " << endl;
        cap.read(frame);
        if(frame.empty())
        {
            cerr << "ERROR! Blank frame grabbed\n";
            break;
        }
        mutex.unlock();
        convertedFrame = convertMat(frame);

        imshow("Live", frame);

        /*
        if(waitKey(5) >= 0)
            break;
        */

    }


}
