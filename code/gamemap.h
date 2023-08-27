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
    //������Ϸ���ָ��
    void setMouse();
    //��ʾ���Ϸ�ѡ��ֲ�ﴰ��
    void showChoosePlantsWidget();
    //��ʱ������������
    void updateSun();
    //��Ϸ����ʱչʾ
    void gameBeginMove();
    //��Ϸ Ready-set-Plant��ʾ
    void showRedReady();
    //��ʼ����ʾֲ�￨��
    void doShowPlantsCard();
    //��ȡ�µ�item����ӵ�scene
    void getNewItem(QGraphicsObject * item);
    //ѡ��ֲ�￨ ��ȡ��������
    void doSpendSunshine(int num);
    //����С�Ƴ�
    void setSmallCar();

    //��ʾ��ʼ��ʬվ��
    void showBeginStandZombies();

    //��д����ƶ��¼�
    void mouseMoveEvent(QMouseEvent *event) override;

    //�ͷſ�ͷ��ʬ
    void deleteBeginZombie();
    //���ò���
    void setSpade();
    //������Ȼ��������
    void setSunshine();

    //��������ʬ
    void outZombies();
    //��⽩ʬ
    bool checkColliding();

    //��������
    static int SunshineNum;
    //��ǰ�����ڽ�ʬ����
    static int ZombiesNum;

private:
    //��Ϸ��ͷѡ������
    gameMedia * beginChooseCardMedia;
    QGraphicsScene * gameScene;
    QGraphicsPixmapItem * backgroundItem;
    //��¼��������
    //int sunNumber;

    QGraphicsPixmapItem * chooseCardWidget;
    QGraphicsProxyWidget * showSunLabel;
    //��ʾ��������
    QLabel * showSun;

    //��Ϸ���������ƶ���ͷ����
    QTimer * leftMove;
    QTimer * rightMove;
    QTimer * downChooseCard;

    //��Ϸ���� ready-set-plant��ʾ
    QGraphicsPixmapItem * showReadyGame;

    //ѡ��ֲ�￨
    PlantsCard * Id_1;
    PlantsCard * Id_2;
    PlantsCard * Id_3;
    PlantsCard * Id_4;
    PlantsCard * Id_5;
    PlantsCard * Id_6;
    //ֲ�￨����
    QVector<PlantsCard **> cards;

    //��ͷվ����ʬ
    QVector<Zombies *> zombiesVector;
    //����
    Sunshine * sunshine;
    //��齩ʬ������ʱ��
    QTimer * checkZombiesTimer;

signals:
    void sendSunshine(int num);
};

#endif // GAMEMAP_H
