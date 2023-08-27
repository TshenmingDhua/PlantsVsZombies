#ifndef SHOOTBOX_H
#define SHOOTBOX_H

#include <QObject>
#include <QGraphicsItem>
#include "plants.h"
#include "peas.h"

class shootBox : public QGraphicsObject
{
    Q_OBJECT
public:
    shootBox(bool isShooter,QGraphicsObject * plant,QObject * parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;

    //检查碰撞
    void checkColliding();

private:
    //判断是否为射手
    bool isShooter;
    Plants * plantItem;
    //范围内是否有僵尸
    bool isHaveZombie;

    //子弹
    Peas * peas;

signals:
    void shootBegin();
    void shootEnd();

};

#endif // SHOOTBOX_H
