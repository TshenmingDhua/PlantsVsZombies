#include "peas.h"
#include <QPainter>
#include <QList>
#include "zombies.h"

Peas::Peas(bool isGreen)
{
    //this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    this->isGreenPeas = isGreen;
    this->media = new gameMedia(":/res/Media/plantPuke.wav",this);
    this->isDelete = false;
    this->moveTimer = new QTimer(this);
    connect(this->moveTimer,&QTimer::timeout,this,&Peas::shoot);
    this->setZValue(99);
    if(isGreen)
    {
        this->filename = ":/res/peas/greenPeas.png";
    }
    else
    {
        this->filename = ":/res/peas/snowPeas.png";
    }

    this->moveTimer->start(26);
    QTimer * check = new QTimer(this);
    connect(check,&QTimer::timeout,this,&Peas::checkColliding);
    check->start(60);
}

void Peas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,this->filename);

//    painter->setPen(Qt::blue); // 设置边框颜色
//    painter->setBrush(Qt::NoBrush); // 不填充颜色
//    painter->drawRect(boundingRect()); // 使用boundingRect()获取图形项的边界矩形并绘制
}

QRectF Peas::boundingRect() const
{
    return QRectF(6,6,16,16);
}

void Peas::shoot()
{
    this->setPos(this->x() + 7,this->y());
}

void Peas::checkColliding()
{
    if(this->isDelete)
    {
        return;
    }
    int num = 0;
    QList<QGraphicsItem *> list = this->collidingItems();
    for(QList<QGraphicsItem *>::iterator it = list.begin();it!=list.end();it++)
    {
        if((*it)->toolTip() == "zombie")
        {
            num++;
            if(num == 2)
            {
                return;
            }
            Zombies * zombie = static_cast<Zombies *>(*it);
            //判断豌豆类型    僵尸行动变慢
            if(!this->isGreenPeas)
            {
                zombie->beIce();
            }
            this->isDelete = true;
            QTimer::singleShot(130,[=](){
                zombie->lessHealth();
                this->moveTimer->stop();
                this->filename = ":/res/peas/Hite.png";
                this->setPos(this->x() - 23,this->y() - 23);
                this->media = new gameMedia(":/res/Media/peaHitZombie.mp3");
                QTimer::singleShot(90,[=](){
                    delete this;
                });
            });
        }
    }
}
