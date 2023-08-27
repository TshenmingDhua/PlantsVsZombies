#include "plantthread.h"
#include <QTimer>
#include <QDebug>
#include <QPixmap>

plantThread::plantThread()
{

}

void plantThread::run()
{
    this->timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&plantThread::startWork);
    this->timer->start(10);
    exec();
}

//void plantThread::startThread()
//{
//    this->thread->start();
//}

void plantThread::startWork()
{
    this->posX += 2;

    emit this->sendPos(this->posX);
}

void plantThread::setPos(int x)
{
    this->posX = x;
}
