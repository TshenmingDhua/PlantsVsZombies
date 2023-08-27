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

    //�����ײ
    void checkColliding();

private:
    //�ж��Ƿ�Ϊ����
    bool isShooter;
    Plants * plantItem;
    //��Χ���Ƿ��н�ʬ
    bool isHaveZombie;

    //�ӵ�
    Peas * peas;

signals:
    void shootBegin();
    void shootEnd();

};

#endif // SHOOTBOX_H
