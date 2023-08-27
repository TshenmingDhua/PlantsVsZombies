#ifndef PLANTS_H
#define PLANTS_H

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QMap>
#include <QPixmap>
#include <QDebug>
#include "zombies.h"

class Plants : public QGraphicsObject
{
    Q_OBJECT
public:
    Plants(int id);
    ~Plants();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    //选卡出现静止植物图案
    void chooseCard();
    //放置植物后 动画
    void setPlantCartoon();
    //初始化植物动画张数
    void doPlantCartoon(int id);
    //随时检查碰撞
    void checkColliding();
    //减少生命值
    void lessHealth();
    //植物射击
    void shoot();
    //植物停止射击
    void stopShoot();
    //土豆雷长大
    void potatoGrowUp();
    //向日葵生产阳光
    void makeSunshine();

    //植物名称
    QString plantName;

    //当前鼠标坐标
    static int mousePosX;
    static int mousePosY;

private:
    //植物编号
    int plantID;
    //植物静止图片
    QMap<int,int> pix;
    //判断植物是否被种植
    bool isSet;

    //判断当前是否有僵尸正在吃植物
    bool isHaveZombieEating;
    //植物生命值
    int plantHealth;
    //减少生命值定时器
    QTimer * eatHealth;

    //选卡拖动计时器
    QTimer * chooseCardTimer;
    //植物动画当前张数
    int cartoonNum;
    //植物动画总共张数
    int allCartoonNum;
    //植物动画切换时间
    QMap<int,int> cartoonTimer;

    //僵尸类
    Zombies * zombie;

    //植物动画文件路径
    QPixmap cartoonFileName;
    QPixmap * cartoonPixmap = new QPixmap;

    //射击豌豆间隔计时器
    QTimer * shootTimer;
    //动画切换计时器
    QTimer * setCartoonTimer;
    //土豆雷长大动画数量 当前数量
    int potatoCartoonNum;
    //植物坐标
    int myPosX;
    int myPosY;
    //判断土豆雷是否长大
    bool potatoTNTIsGrowUp;
    //判断土豆雷是否爆炸
    bool potatoTNTIsBang;

    //场景
    QGraphicsScene * gameScene;

signals:
    void eatOver();

};

#endif // PLANTS_H
