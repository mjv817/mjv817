#include "dialog.h"
#include "ui_dialog.h"
#include "videoheader.h"
#include <QPixmap>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    mThread = new MyThread(this);
    connect(mThread,SIGNAL(NumberChanged(int)),this,SLOT(onNumberChanged(int)));


    videoThread = new VideoThread(this);
    //connect(videoThread,SIGNAL(FrameChanged(cv::Mat)),this,SLOT(onFrameChanged(cv::Mat)));



    connect(videoThread,SIGNAL(ConvertedFrameChanged(QImage)),this,SLOT(onFrameChanged(QImage)));
    //createImageLabel();


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::onNumberChanged(int Number)
{
    ui->label->setText(QString::number(Number));
}

void Dialog::onFrameChanged(QImage testImage)
{
    ui->label_5->setPixmap(QPixmap::fromImage(testImage));
}

void Dialog::on_pushButton_clicked()
{
    //Started
    mThread->start();
}

void Dialog::on_pushButton_2_clicked()
{
    //Stopped
    mThread->Stop = true;
}

void Dialog::on_pushButton_3_clicked()
{
    videoThread->start(QThread::HighestPriority);
    videoThread->doCapture = true;
}

void Dialog::createImageLabel()
{
    cv::Mat image = cv::imread("/home/mjv817/QTProjects/DockingExample/ms2.jpg");
    cv::resize(image, image, Size(512,384),0,0,INTER_LINEAR);
    cv::cvtColor(image,image,CV_BGR2RGB);
    QImage imdisplay((uchar*)image.data,image.cols,image.rows,image.step, QImage::Format_RGB888);


    ui->label_5->setPixmap(QPixmap::fromImage(imdisplay));


}

void Dialog::on_pushButton_4_clicked()
{
    videoThread->doCapture = false;
}
