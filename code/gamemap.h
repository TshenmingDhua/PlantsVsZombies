#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include "plantscard.h"
#include <QVector>
#include "cooldowndark.h"
#include "gamemedia.h"
#include "zombies.h"
#include "sunshine.h"

class gameMap : public QGraphicsView
{
    Q_OBJECT
public:
    explicit gameMap(QGraphicsView *parent = nullptr);
    //设置游戏鼠标指针
    void setMouse();
    //显示最上方选择植物窗口
    void showChoosePlantsWidget();
    //随时更新阳光数量
    void updateSun();
    //游戏开局时展示
    void gameBeginMove();
    //游戏 Ready-set-Plant提示
    void showRedReady();
    //初始换显示植物卡牌
    void doShowPlantsCard();
    //获取新的item并添加到scene
    void getNewItem(QGraphicsObject * item);
    //选择植物卡 扣取阳光总数
    void doSpendSunshine(int num);
    //设置小推车
    void setSmallCar();

    //显示初始僵尸站立
    void showBeginStandZombies();

    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;

    //释放开头僵尸
    void deleteBeginZombie();
    //设置铲子
    void setSpade();
    //设置自然生成阳光
    void setSunshine();

    //正常出僵尸
    void outZombies();
    //检测僵尸
    bool checkColliding();

    //阳光总数
    static int SunshineNum;
    //当前场景内僵尸数量
    static int ZombiesNum;

private:
    //游戏开头选卡音乐
    gameMedia * beginChooseCardMedia;
    QGraphicsScene * gameScene;
    QGraphicsPixmapItem * backgroundItem;
    //记录阳光总数
    //int sunNumber;

    QGraphicsPixmapItem * chooseCardWidget;
    QGraphicsProxyWidget * showSunLabel;
    //显示阳光数量
    QLabel * showSun;

    //游戏开局左右移动镜头动画
    QTimer * leftMove;
    QTimer * rightMove;
    QTimer * downChooseCard;

    //游戏开局 ready-set-plant显示
    QGraphicsPixmapItem * showReadyGame;

    //选择植物卡
    PlantsCard * Id_1;
    PlantsCard * Id_2;
    PlantsCard * Id_3;
    PlantsCard * Id_4;
    PlantsCard * Id_5;
    PlantsCard * Id_6;
    //植物卡容器
    QVector<PlantsCard **> cards;

    //开头站立僵尸
    QVector<Zombies *> zombiesVector;
    //阳光
    Sunshine * sunshine;
    //检查僵尸数量计时器
    QTimer * checkZombiesTimer;

signals:
    void sendSunshine(int num);
};

#endif // GAMEMAP_H
