#include "spade.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "plants.h"
#include <QList>
#include "setplants.h"
#include "gamemedia.h"

Spade::Spade(QGraphicsScene * myScene,QObject * parent)
{
    if(parent != nullptr)
    {
        this->setParent(parent);
    }
    myScene->addItem(this);
    this->setZValue(90);
    this->isTake = false;

    this->moveTimer = new QTimer(this);
    connect(this->moveTimer,&QTimer::timeout,this,&Spade::move);
}

void Spade::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,QPixmap(":/res/spade/spade.png"));

    //������ײ
//    painter->setPen(Qt::yellow); // ���ñ߿���ɫ
//    painter->setBrush(Qt::NoBrush); // �������ɫ
//    painter->drawRect(boundingRect()); // ʹ��boundingRect()��ȡͼ����ı߽���β�����
}

QRectF Spade::boundingRect() const
{
    return QRectF(10,10,63,63);
}

void Spade::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->isTake)
    {
        gameMedia * takeMedia = new gameMedia(":/res/Media/spade.mp3",this);
        this->moveTimer->start(16);
        this->isTake = true;
    }
    else
    {
        QList<QGraphicsItem *> list = this->collidingItems();
        for(QList<QGraphicsItem *>::iterator it = list.begin();it!=list.end();it++)
        {
            if((*it)->toolTip() == "plant")
            {
                Plants * plant = static_cast<Plants *>(*it);
                setPlants::deletePos(plant->x() + 30,plant->y() + 60);
                delete plant;
                break;
            }
        }
        this->moveTimer->stop();
        this->isTake = false;
        this->setPos(776,0);
    }
}

void Spade::move()
{
    this->setPos(Plants::mousePosX,Plants::mousePosY);
}
