#ifndef SPADE_H
#define SPADE_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QTimer>

class Spade : public QGraphicsObject
{
    Q_OBJECT
public:
    Spade(QGraphicsScene * myScene,QObject * parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    //��������ƶ�����
    void move();

private:
    //�Ƿ��������Ų���
    bool isTake;
    //�ƶ���ʱ��
    QTimer * moveTimer;

signals:

};

#endif // SPADE_H
