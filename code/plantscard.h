#ifndef PLANTSCARD_H
#define PLANTSCARD_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include "cooldowndark.h"
#include "gamemedia.h"

class PlantsCard : public QGraphicsObject
{
    Q_OBJECT
public:
    PlantsCard(int Id,int x,int y);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    //植物卡牌冷却
    void coolDown();
    //获取阳光
    void getSunshine();
    //检查阳光是否充足
    void checkSunshineEnough();
    //放置植物
    void setPlant();

private:
    //卡牌编号
    int CardId;
    //当前植物需要的阳光数量
    int myPrice;
    //阳光总数
    int sunshineNumber;
    //判断卡牌是否正在冷却中
    bool isCooldown;
    //判断是否有足够的阳光选择当前植物
    bool isEnoughSunshine;
    //冷却阴影类
    coolDownDark * dark;
    //场景类
    QGraphicsScene * sce;

signals:
    //发送item
    void sendNewItem(QGraphicsObject * item);
    //购买植物成功 扣取阳光信号
    void spendSunshine(int num);
    //随时发送当前鼠标坐标
    void sendMousePos(int x,int y);

};

#endif // PLANTSCARD_H
