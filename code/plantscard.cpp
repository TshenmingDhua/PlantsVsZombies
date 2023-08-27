#include "plantscard.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTimer>
#include "gamemedia.h"
#include "cooldowndark.h"
#include "QMap"
#include "QGraphicsPixmapItem"
#include "plants.h"
#include "gamemap.h"

PlantsCard::PlantsCard(int Id,int x,int y)
{
    this->CardId = Id;
    this->setPos(QPointF(x,y));
    this->setZValue(10);

    QTimer * getSunTimer = new QTimer(this);
    connect(getSunTimer,&QTimer::timeout,this,&PlantsCard::getSunshine);
    getSunTimer->start(90);

    //��ʼ����ǰֲ����Ҫ����������
    int price[6] = {50,100,175,200,25,50};
    this->myPrice = price[Id - 1];

    //��ʼ������Ϊ ���ⲻ��
    this->isEnoughSunshine = false;
    //��ʼ��������
    this->sce = this->scene();
    //��ȴ
    this->coolDown();
}

void PlantsCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(Qt::red); // ���ñ߿���ɫ
//    painter->setBrush(Qt::NoBrush); // �������ɫ
//    painter->drawRect(boundingRect()); // ʹ��boundingRect()��ȡͼ����ı߽���β�����

    //��������Ƿ����
    this->checkSunshineEnough();

    //res��Դ��ַ
    QString CardAddress = "";
    if(!this->isEnoughSunshine || this->isCooldown)
    {
    CardAddress = ":/res/plantsCard/darkCard/Dark-";
    }
    else
    {
    CardAddress = ":/res/plantsCard/";
    }

    switch (this->CardId)
    {
    case 1:
        painter->drawPixmap(0,0,QPixmap(CardAddress += "sunFlowerCard.png"));
        break;
    case 2:
        painter->drawPixmap(0,0,QPixmap(CardAddress += "greenPeasShooterCard.png"));
        break;
    case 3:
        painter->drawPixmap(0,0,QPixmap(CardAddress += "snowShooterCard.png"));
        break;
    case 4:
        painter->drawPixmap(0,0,QPixmap(CardAddress += "doubleGreenPeasShooterCard.png"));
        break;
    case 5:
        painter->drawPixmap(0,0,QPixmap(CardAddress += "potatoTNTCard.png"));
        break;
    case 6:
        painter->drawPixmap(0,0,QPixmap(CardAddress += "normalNutCard.png"));
        break;
    }
}

QRectF PlantsCard::boundingRect() const
{
    return QRectF(0,0,50,69);
}

void PlantsCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //�ж�������ⲻ��
        if(!this->isEnoughSunshine || this->isCooldown)
        {
            gameMedia * notEnough = new gameMedia(":/res/Media/sunshineNotEnoughMusic.mp3",this);
            return;
        }
        //�������
        else
        {
            gameMedia * choosePlant = new gameMedia(":/res/Media/choosePlant.wav");
            //��ȴ
            this->coolDown();
            //������������
            emit this->spendSunshine(this->myPrice);
            //��ʼ��ֲ��
            Plants * plants = new Plants(this->CardId);
            emit this->sendNewItem(plants);
        }
    }
}

void PlantsCard::coolDown()
{
    int time[6] = {7500,7500,7500,7500,30000,30000};
    this->isCooldown = true;
    this->dark = new coolDownDark(this->x(),this->y(),time[this->CardId - 1]);
    connect(dark,&coolDownDark::CoolDownEnd,this,[=](){this->isCooldown = false;});
    QTimer::singleShot(3,[=](){
        emit this->sendNewItem(dark);
    });
}

void PlantsCard::getSunshine()
{
    this->sunshineNumber = gameMap::SunshineNum;
}

void PlantsCard::checkSunshineEnough()
{
    if(this->myPrice > this->sunshineNumber)
    {
        this->isEnoughSunshine = false;
    }
    else
    {
        this->isEnoughSunshine = true;
    }
}

void PlantsCard::setPlant()
{
    QString plantName[] = {"sunflower"};
    QString name = plantName[this->CardId - 1];
    //��ȡͼƬ
    QMap<QString,int> map;
    map.insert("sunflower",6);

    name =":/res/plants/sunflower/" + name + QString::number(map.value(name)) + ".png";
}
