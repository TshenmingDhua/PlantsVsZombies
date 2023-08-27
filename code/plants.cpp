#include "plants.h"
#include <QMap>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include "plantscard.h"
#include <QTimer>
#include "setplants.h"
#include "plantthread.h"
#include "gamemedia.h"
#include <QList>
#include "zombies.h"
#include "shootbox.h"
#include "peas.h"
#include <QOpenGLWidget>
#include "sunshine.h"

Plants::Plants(int id)
{
    this->plantID = id;
    this->setToolTip("plant");
    this->isSet = false;
    this->potatoTNTIsBang = false;
    this->potatoTNTIsGrowUp = false;
    this->pix = {{1,6},{2,3},{3,3},{4,3},{5,1},{6,3}};
    this->setZValue(26);
    this->cartoonNum = 1;
    this->potatoCartoonNum = 1;
    this->shootTimer = new QTimer(this);
    connect(shootTimer,&QTimer::timeout,this,[=](){
        bool isSnowPeas;
        if(this->plantName == "snowShooter")
        {
            isSnowPeas = false;
        }
        else
        {
            isSnowPeas = true;
        }

        Peas * pea = new Peas(isSnowPeas);
        pea->setPos(this->x() + 53,this->y());
        (this->scene())->addItem(pea);
        if(this->plantName == "doubleGreenPeasShooter")
        {
            QTimer::singleShot(160,[=](){
                Peas * pea = new Peas(isSnowPeas);
                pea->setPos(this->x() + 53,this->y());
                (this->scene())->addItem(pea);
            });
        }
    });

    QString names[] = {"sunflower","greenPeasShooter","snowShooter","doubleGreenPeasShooter","potatoTNTBegin","normalNut"};
    //动画时间
    this->cartoonTimer = {{1,60},{2,83},{3,83},{4,76},{5,80},{6,75}};
    this->plantName = names[this->plantID - 1];

    //初始化植物张数
    this->doPlantCartoon(this->plantID);
    //测试拖动
    this->chooseCard();

    //初始化生命值
    if(this->plantName == "normalNut")
    {
        this->plantHealth = 30;
    }
    else
    {
        this->plantHealth = 6;
    }
    this->eatHealth = new QTimer(this);
    connect(this->eatHealth,&QTimer::timeout,this,&Plants::lessHealth);
    this->isHaveZombieEating = false;

    //检测碰撞
    QTimer * checkTimer = new QTimer;
    connect(checkTimer,&QTimer::timeout,this,&Plants::checkColliding);
    checkTimer->start(130);
}

Plants::~Plants()
{
    QList<QGraphicsItem *> list = this->collidingItems();
    for(QList<QGraphicsItem *>::iterator it = list.begin();it!=list.end();it++)
    {
        if((*it)->toolTip() == "zombie")
        {
            Zombies * zom = static_cast<Zombies *>(*it);
            connect(this,&Plants::eatOver,zom,&Zombies::eatOver);
            emit this->eatOver();
            return;
        }
    }
}

void Plants::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //如果没有被种植的情况
    if(!this->isSet)
    {
        QString addr = ":/res/plants/" + this->plantName + "/a (";
        addr = addr + QString::number(pix.value(this->plantID)) + ").png";
        painter->drawPixmap(0,0,QPixmap(addr));
    }
    else
    {
        painter->drawPixmap(0,0,cartoonFileName);
    }

    //绘制碰撞
//        painter->setPen(Qt::red); // 设置边框颜色
//        painter->setBrush(Qt::NoBrush); // 不填充颜色
//        painter->drawRect(boundingRect()); // 使用boundingRect()获取图形项的边界矩形并绘制
}

QRectF Plants::boundingRect() const
{
    if(this->plantName == "potatoTNTBegin")
    {
        return QRectF(-5,-30,66,69);
    }
    return QRectF(0,0,66,69);
}

void Plants::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->isSet)
    {
        if(event->button() == Qt::LeftButton)
        {
            QVector<int> vector = setPlants::setPlantInSquare(this->pos().x() + 30,this->pos().y() + 60);
            if(*(vector.begin()) == -1)
            {
                return;
            }
            this->chooseCardTimer->stop();
            if(this->plantName == "potatoTNTBegin")
            {
                this->setPos(vector[0] + 20,vector[1] + 40);
                this->myPosX = this->x() - 30;this->myPosY = this->y() -20;
                QTimer::singleShot(3000,this,&Plants::potatoGrowUp);
            }
            else
            {
                this->setPos(vector[0],vector[1]);
                if(this->plantName == "sunflower")
                {
                    this->makeSunshine();
                }
            }
            this->setPlantCartoon();
            this->isSet = true;
            gameMedia * media = new gameMedia(":/res/Media/setPlant.wav");

            //僵尸检测
            if(this->plantName == "sunflower" || this->plantName == "normalNut" || this->plantName == "potatoTNTBegin")
            {
                return;
            }
            shootBox * box = new shootBox(true,this,this);

    //        qDebug()<<vector[0]<<vector[1];
    //        qDebug()<<"x="<<this->pos().x()<<"\ty="<<this->pos().y();
        }
    }

}

void Plants::chooseCard()
{
    this->chooseCardTimer = new QTimer;
    connect(chooseCardTimer,&QTimer::timeout,this,[=](){
        if(this->plantName == "potatoTNTBegin")
        {
            this->setPos(Plants::mousePosX + 20,Plants::mousePosY + 40);
        }
        else
        {
            this->setPos(Plants::mousePosX,Plants::mousePosY);
        }

    });
    chooseCardTimer->start(10);
}

void Plants::setPlantCartoon()
{
//    plantThread * thread = new plantThread;
//    connect(thread,&plantThread::changePic,this,[=](QPixmap pix){
//        this->cartoonFileName = pix;
//    });
//    thread->start();

    //测试强制paint
    QTimer * paint = new QTimer;
    connect(paint,&QTimer::timeout,this,[=](){
        this->update();
    });
    paint->start(10);

    this->setCartoonTimer = new QTimer;
    connect(setCartoonTimer,&QTimer::timeout,this,[=](){
        QString addr = ":/res/plants/" + this->plantName +"/a (" + QString::number(this->cartoonNum) + ").png";
        this->cartoonNum ++;
        if(cartoonNum == this->allCartoonNum + 1)
        {
            this->cartoonNum = 1;
        }
        this->cartoonFileName = addr;
    });
    setCartoonTimer->start(this->cartoonTimer.value(this->plantID));
}

void Plants::doPlantCartoon(int id)
{
    switch(id)
    {
    case 1:
        this->allCartoonNum = 27;
        break;
    case 2:
        this->allCartoonNum = 12;
        break;
    case 3:
        this->allCartoonNum = 15;
        break;
    case 4:
        this->allCartoonNum = 15;
        break;
    case 5:
        this->allCartoonNum = 1;
        break;
    case 6:
        this->allCartoonNum = 16;
    }
}

void Plants::checkColliding()
{
    if(!this->isSet)
    {
        return;
    }

    QList<QGraphicsItem *> list = this->collidingItems();
    for(QList<QGraphicsItem*>::iterator it = list.begin();it!=list.end();it++)
    {
        if((*(*it)).toolTip() == "zombie")
        {
            if(this->isHaveZombieEating)
            {
               return;
            }
            this->zombie = static_cast<Zombies *>(*it);
            if(this->potatoTNTIsGrowUp)
            {
                if(!this->potatoTNTIsBang)
                {
                    gameMedia * media = new gameMedia(":/res/Media/potatoTNTBang.wav");
                    this->potatoTNTIsBang = true;
                    setPlants::deletePos(this->x(),this->y());
                    zombie->dead();
                    QTimer::singleShot(1300,[=](){
                        delete this;
                    });
                }
                return;
            }
            this->zombie->doEating();
            this->eatHealth->start(553);
            if(this->zombie->isBeIce)
            {
                this->eatHealth->setInterval(1600);
            }
            this->isHaveZombieEating = true;
            return;
        }
    }
    this->isHaveZombieEating = false;
    this->eatHealth->stop();
}

void Plants::lessHealth()
{
    if(this->zombie->isDead)
    {
        return;
    }

    this->plantHealth--;
    if(this->plantHealth == 0)
    {
        //调用僵尸吃完植物函数
        this->zombie->eatOver();
        if(this->plantName == "potatoTNTBegin")
        {
            setPlants::deletePos(this->x() + 30,this->y() + 30);
        }
        else
        {
            setPlants::deletePos(this->x() + 30,this->y() + 60);
        }

        delete this;
    }
}

void Plants::shoot()
{
    this->shootTimer->start(2000);
}

void Plants::stopShoot()
{
    this->shootTimer->stop();
}

void Plants::potatoGrowUp()
{
    this->setCartoonTimer->stop();
    this->potatoTNTIsGrowUp = true;
    QTimer * timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        this->setPos(this->myPosX,this->myPosY);
        if(this->potatoTNTIsBang)
        {
            QString addr = ":/res/potatoTNT/potatoTNTBang.png";
            this->cartoonFileName = addr;
            return;
        }
        QString addr = ":/res/potatoTNT/a (";
        addr = addr + QString::number(this->potatoCartoonNum) + ").png";
        this->cartoonFileName = addr;
        this->potatoCartoonNum++;
        if(this->potatoCartoonNum == 9)
        {
            potatoCartoonNum = 1;
        }
    });
    timer->start(189);
}

void Plants::makeSunshine()
{
    QTimer::singleShot(1000,[=](){
        Sunshine * sun = new Sunshine(this->scene());
        sun->setPos(this->x() + 10,this->y() + 10);

        QTimer * make = new QTimer(this);
        connect(make,&QTimer::timeout,this,[=](){
            Sunshine * sun = new Sunshine(this->scene());
            sun->setPos(this->x() + 10,this->y() + 10);
        });

        make->start(20000);
    });
}

int Plants::mousePosX = 0;
int Plants::mousePosY = 0;
