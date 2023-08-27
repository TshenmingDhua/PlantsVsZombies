#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QTimer>
#include "gamemedia.h"

class Zombies : public QGraphicsObject
{
    Q_OBJECT
public:
    Zombies(QString name,bool isStand,QGraphicsScene * scene,QObject * parents = nullptr);
    ~Zombies();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;

    //设置僵尸动画
    void loadZombieCartoon();
    //设置僵尸动画图片数量
    void setCartoonPixmap();
    //僵尸行走
    void goWalk();
    //僵尸吃植物
    void doEating();
    //吃完植物
    void eatOver();
    //减少生命值
    void lessHealth();
    //死亡动画
    void dead();
    //被冰冻减速
    void beIce();

    //是否已经死亡
    bool isDead;
    //是否被冰冻
    bool isBeIce;

private:
    QString m_Name;
    bool isStand;
    //判断是否正在吃植物
    bool isEating;

    //当前僵尸图片路径
    QString zombiePixmap;
    //僵尸动画切换速度
    int cartoonSpeed;
    //当前僵尸动画图片数量 第几个
    int cartoonNum;
    //总共僵尸动画图片数量
    int allCartoonNum;
    //僵尸吃植物动画总数
    int allEatCartoonNum;

    //僵尸生命值 普通10，路障30
    int health;

    //走路定时器
    QTimer * walkTimer;
    //吃植物音频
    gameMedia * eatMedia;

    //已经delete
    bool isDelete;
    //记录死亡动画数量 当前数量
    int deadCartoonNum;
    //动画计时器
    QTimer * cartoonTimer;

signals:

};

#endif // ZOMBIES_H
