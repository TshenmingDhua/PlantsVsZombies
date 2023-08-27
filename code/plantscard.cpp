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

    //初始化当前植物需要的阳光数量
    int price[6] = {50,100,175,200,25,50};
    this->myPrice = price[Id - 1];

    //初始化阳光为 阳光不足
    this->isEnoughSunshine = false;
    //初始化场景类
    this->sce = this->scene();
    //冷却
    this->coolDown();
}

void PlantsCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(Qt::red); // 设置边框颜色
//    painter->setBrush(Qt::NoBrush); // 不填充颜色
//    painter->drawRect(boundingRect()); // 使用boundingRect()获取图形项的边界矩形并绘制

    //检查阳光是否充足
    this->checkSunshineEnough();

    //res资源地址
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
        //判断如果阳光不够
        if(!this->isEnoughSunshine || this->isCooldown)
        {
            gameMedia * notEnough = new gameMedia(":/res/Media/sunshineNotEnoughMusic.mp3",this);
            return;
        }
        //阳光充足
        else
        {
            gameMedia * choosePlant = new gameMedia(":/res/Media/choosePlant.wav");
            //冷却
            this->coolDown();
            //减少阳光总数
            emit this->spendSunshine(this->myPrice);
            //初始化植物
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
    //获取图片
    QMap<QString,int> map;
    map.insert("sunflower",6);

    name =":/res/plants/sunflower/" + name + QString::number(map.value(name)) + ".png";
}
