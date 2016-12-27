#include "mythread.h"
#include <QtCore>
#include <iostream>
using namespace std;

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{

}


void MyThread::run()
{
    int i;
    for(i = 0; i < 10000; i++)
    {
        QMutex mutex;
        mutex.lock();

        if(this->Stop) break;
        mutex.unlock();

        emit NumberChanged(i);

        this->msleep(100);

    }
}
