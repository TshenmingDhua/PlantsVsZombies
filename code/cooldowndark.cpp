#include "cooldowndark.h"
#include <QPainter>
#include <QDebug>

coolDownDark::coolDownDark(int x,int y,int time)
{
    this->goUp = new QTimer(this);
    this->upTime = time / 76;
    connect(goUp,&QTimer::timeout,this,[=](){
        this->setPos(this->x(),this->y() - 1);
        if(this->y() <= -70)
        {
            this->goUp->stop();
            //发送结束冷却信号
            emit this->CoolDownEnd();
        }
    });

    QFile * mediaFile = new QFile(":/res/Media/sunshineNotEnoughMusic.mp3");
    this->media = new QMediaPlayer(this);
    if(!mediaFile->open(QIODevice::ReadOnly))
    {
        qDebug()<<"open error";
        return;
    }
    this->media->setMedia(QMediaContent(),mediaFile);
    this->media->setVolume(50);
    this->setPos(x,y);
    this->setZValue(23);

    this->goUp->start(this->upTime);
}

void coolDownDark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,QPixmap(":/res/plantsCard/darkCard/coolDownDark.png"));

//    painter->setPen(Qt::blue); // 设置边框颜色
//    painter->setBrush(Qt::NoBrush); // 不填充颜色
//    painter->drawRect(boundingRect()); // 使用boundingRect()获取图形项的边界矩形并绘制
}

QRectF coolDownDark::boundingRect() const
{
    return QRectF(0,0,50,69);
}
