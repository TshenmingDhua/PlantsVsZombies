#include "smallcar.h"
#include <QPainter>
#include <QTimer>
#include "zombies.h"
#include <QList>
#include "gamemedia.h"
#include "plantthread.h"
#include <QPropertyAnimation>

smallCar::smallCar(QGraphicsScene * myScene,QObject * parent)
{
    this->posX = 0;

    this->setZValue(50);
    this->isStart = false;
    this->myScene = myScene;
    this->myScene->addItem(this);
    if(parent != nullptr)
    {
        this->setParent(parent);
    }

    //��ʱ�����ײ
    QTimer * check = new QTimer(this);
    connect(check,&QTimer::timeout,this,&smallCar::checkColliding);
    check->start(189);
}

void smallCar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,QPixmap(":/res/smallCar/car.png"));

    //������ײ
//    painter->setPen(Qt::yellow); // ���ñ߿���ɫ
//    painter->setBrush(Qt::NoBrush); // �������ɫ
//    painter->drawRect(boundingRect()); // ʹ��boundingRect()��ȡͼ����ı߽���β�����
}

QRectF smallCar::boundingRect() const
{
    return QRectF(0,0,73,60);
}

void smallCar::checkColliding()
{
    QList<QGraphicsItem *> list = this->collidingItems();
    for(QList<QGraphicsItem *>::iterator it = list.begin();it!=list.end();it++)
    {
        if((*it)->toolTip() == "zombie")
        {
            //�ж��Ƿ��Ѿ�����
            if(!this->isStart)
            {
                this->isStart = true;
                //��ʼ�ƶ�
                this->carMove();
                gameMedia * start = new gameMedia(":/res/Media/smallCarStart.wav",this);
                start->setSlow();
            }
            Zombies * zombie = static_cast<Zombies *> (*it);
            zombie->dead();
        }
    }
}

void smallCar::carMove()
{
    this->move = new QTimer(this);
    connect(move,&QTimer::timeout,this,[=](){
        this->setPos(this->x() + 9,this->y());
        if(this->x() >= 1300)
        {
            this->move->stop();
            delete this;
        }
    });
    move->start(23);


//    QPropertyAnimation *animation = new QPropertyAnimation(this,"pos");
//    animation->setDuration(5000);
//    animation->setStartValue(QPointF(this->x(),this->y()));
//    animation->setEndValue(QPointF(this->x() + 900,this->y()));
//    animation->start();
}
