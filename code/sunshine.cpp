#include "sunshine.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "gamemedia.h"
#include "gamemap.h"

Sunshine::Sunshine(QGraphicsScene * myScene,QObject * parent)
{
    if(parent != nullptr)
    {
        this->setParent(parent);
    }
    myScene->addItem(this);
    this->isMove = false;
    this->setZValue(93);
    this->pixNum = 1;
    this->bigsunX = 230;
    this->bigsunY = 5;

    this->pixAddr = "";
    this->cartoonTimer = new QTimer(this);
    connect(this->cartoonTimer,&QTimer::timeout,this,&Sunshine::loadCartoon);
    this->cartoonTimer->start(60);
    QTimer::singleShot(6000,this,&Sunshine::clearMe);
}

void Sunshine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,this->pixAddr);

    //绘制碰撞
//    painter->setPen(Qt::blue); // 设置边框颜色
//    painter->setBrush(Qt::NoBrush); // 不填充颜色
//    painter->drawRect(boundingRect()); // 使用boundingRect()获取图形项的边界矩形并绘制
}

QRectF Sunshine::boundingRect() const
{
    return QRectF(13,13,49,49);
}

void Sunshine::loadCartoon()
{
    QString addr =":/res/sunshine/a (" + QString::number(this->pixNum) + ").png";
    this->pixAddr = addr;
    this->pixNum++;
    if(this->pixNum == 23)
    {
        this->pixNum = 1;
    }
}

void Sunshine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->isMove)
    {
        return;
    }
    this->goMove();
    gameMedia * media = new gameMedia(":/res/Media/getSunshine.wav");
    gameMap::SunshineNum += 25;
}

void Sunshine::goMove()
{
    this->isMove = true;
    int x,y;
    x = this->x();
    y = this->y();

    //移动动画
    QPropertyAnimation * animation = new QPropertyAnimation(this,"pos");
    animation->setParent(this);
    animation->setDuration(700);
    animation->setStartValue(QPointF(x,y));
    animation->setEndValue(QPointF(230,5));
    animation->start();
    QTimer::singleShot(700,[=](){
        delete this;
    });
}

void Sunshine::clearMe()
{
    //判断是否为自然阳光
    if(this->natureAnimation == nullptr)
    {
        return;
    }
    this->cartoonTimer->stop();
    delete this;
}

void Sunshine::natureSunshine(int x, int y)
{
    this->natureAnimation = new QPropertyAnimation(this,"pos");
    this->natureAnimation->setParent(this);
    this->natureAnimation->setDuration(4000);
    this->natureAnimation->setStartValue(QPointF(x,-30));
    this->natureAnimation->setEndValue(QPointF(x,y));
    this->natureAnimation->start();
    QTimer::singleShot(10000,this,&Sunshine::clearMe);
}
