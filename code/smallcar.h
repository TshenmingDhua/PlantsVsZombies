#ifndef SMALLCAR_H
#define SMALLCAR_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QTimer>

class smallCar : public QGraphicsObject
{
    Q_OBJECT
public:
    smallCar(QGraphicsScene * myScene,QObject * parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;

    //检查碰撞
    void checkColliding();
    //小车启动
    void carMove();
private:
    QGraphicsScene * myScene;
    bool isStart;

    QTimer * move;

    //坐标测试
    int posX;

signals:

};

#endif // SMALLCAR_H
