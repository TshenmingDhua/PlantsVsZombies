#include "gamemedia.h"
#include <QFile>
#include <QDebug>

gameMedia::gameMedia(QString address,QObject * parent,bool dontPlay)
{
    this->foreverTimer = new QTimer(this);
    this->media = new QMediaPlayer(this);
    this->setParent(parent);
    QFile * file = new QFile(address);
    //检查是否成功打开文件
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug()<<"open error!";
        return;
    }
    this->media->setMedia(QMediaContent(),file);

    //设置音量为50
    this->media->setVolume(50);
    if(!dontPlay)
    {
        this->media->play();
    }
}

void gameMedia::playMedia()
{
    this->media->play();
}

void gameMedia::stopMedia(bool isSlow)
{
    QTimer * timer = new QTimer;
    if(!isSlow)
    {
        timer->stop();
        this->media->stop();
        return;
    }

    connect(timer,&QTimer::timeout,this,[=](){
        this->media->setVolume(this->media->volume() - 2);
        if(this->media->volume() <3)
        {
            timer->stop();
            this->media->stop();
        }
    });
    timer->start(80);
}

void gameMedia::setForeverPlay(QString address)
{
    connect(foreverTimer,&QTimer::timeout,this,[=](){
        if(this->media->state() != QMediaPlayer::PlayingState)
        {
            QFile * file = new QFile(address);
            //检查是否成功打开文件
            if(!file->open(QIODevice::ReadOnly))
            {
                qDebug()<<"open error!";
                return;
            }
            this->media->setMedia(QMediaContent(),file);
            this->media->setVolume(50);
            this->media->play();
        }
    });
    foreverTimer->start(10);
}

void gameMedia::stopForeverPlay()
{
    this->foreverTimer->stop();
}

void gameMedia::setSlow()
{
    this->media->setPlaybackRate(0.8);
}
