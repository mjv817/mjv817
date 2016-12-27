#ifndef VIDEOHEADER_H
#define VIDEOHEADER_H

#include <QMainWindow>
#include <QThread>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

class QListWidget;
class QMenu;
class QTextEdit;

class QWidget;
class QLabel;
class QLineEdit;
class QHBoxLayout;
class QGroupBox;
class QVBoxLayout;
class QImage;

class VideoHeader : public QThread
{
    Q_OBJECT
public:
    VideoHeader();
    void createCapture();
private:
    QImage convertMat(const cv::Mat &inMat);
    void processFrame(const cv::Mat &imageIn, const cv::Mat &imageOut);
    void videoCap();
    QHBoxLayout *videoLayout;
    QLabel *videoLabel;
    QGroupBox *videoBox;







};



#endif // VIDEOHEADER_H
