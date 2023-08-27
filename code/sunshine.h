#ifndef SUNSHINE_H
#define SUNSHINE_H

#include <QObject>
#include <QGraphicsObject>
#include <QTimer>
#include <QPropertyAnimation>

class Sunshine : public QGraphicsObject
{
    Q_OBJECT
public:
    Sunshine(QGraphicsScene * myScene,QObject * parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    //更新动画
    void loadCartoon();
    //移动并增加阳光
    void goMove();
    //长时间不收集自动消失
    void clearMe();
    //自然生成阳光动画
    void natureSunshine(int x,int y);

private:
    QString pixAddr;
    //当前动画数量
    int pixNum;

    //目标大太阳坐标
    int bigsunX;
    int bigsunY;
    QTimer * move;
    //是否已经被点击
    bool isMove;
    //动画计时器
    QTimer * cartoonTimer;
    //自然阳光动画类
    QPropertyAnimation * natureAnimation;

signals:
    //增加阳光
    void addSunNum();

};

#endif // SUNSHINE_H
