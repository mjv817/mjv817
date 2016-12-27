#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "mythread.h"
#include "videothread.h"
#include "videoheader.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
namespace Ui {

class QWidget;
class QLabel;
class QHBoxLayout;
class QGroupBox;
class QImage;


class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    MyThread *mThread;
    VideoThread *videoThread;
    VideoHeader *videoHeader;

private:
    Ui::Dialog *ui;
    QLabel *imagelabel;
    QHBoxLayout *imageLayout;
    QHBoxLayout *mainLayout;
    void createImageLabel();



public slots:
    void onNumberChanged(int);
    void onFrameChanged(QImage);



private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    //void on_label_5_linkActivated(const QString &link);
    void on_pushButton_4_clicked();
};

#endif // DIALOG_H
