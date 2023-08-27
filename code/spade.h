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

    //跟随鼠标移动函数
    void move();

private:
    //是否正在拿着铲子
    bool isTake;
    //移动计时器
    QTimer * moveTimer;

signals:

};

#endif // SPADE_H
