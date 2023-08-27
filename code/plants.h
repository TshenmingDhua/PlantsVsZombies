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

    //ѡ�����־�ֲֹ��ͼ��
    void chooseCard();
    //����ֲ��� ����
    void setPlantCartoon();
    //��ʼ��ֲ�ﶯ������
    void doPlantCartoon(int id);
    //��ʱ�����ײ
    void checkColliding();
    //��������ֵ
    void lessHealth();
    //ֲ�����
    void shoot();
    //ֲ��ֹͣ���
    void stopShoot();
    //�����׳���
    void potatoGrowUp();
    //���տ���������
    void makeSunshine();

    //ֲ������
    QString plantName;

    //��ǰ�������
    static int mousePosX;
    static int mousePosY;

private:
    //ֲ����
    int plantID;
    //ֲ�ﾲֹͼƬ
    QMap<int,int> pix;
    //�ж�ֲ���Ƿ���ֲ
    bool isSet;

    //�жϵ�ǰ�Ƿ��н�ʬ���ڳ�ֲ��
    bool isHaveZombieEating;
    //ֲ������ֵ
    int plantHealth;
    //��������ֵ��ʱ��
    QTimer * eatHealth;

    //ѡ���϶���ʱ��
    QTimer * chooseCardTimer;
    //ֲ�ﶯ����ǰ����
    int cartoonNum;
    //ֲ�ﶯ���ܹ�����
    int allCartoonNum;
    //ֲ�ﶯ���л�ʱ��
    QMap<int,int> cartoonTimer;

    //��ʬ��
    Zombies * zombie;

    //ֲ�ﶯ���ļ�·��
    QPixmap cartoonFileName;
    QPixmap * cartoonPixmap = new QPixmap;

    //����㶹�����ʱ��
    QTimer * shootTimer;
    //�����л���ʱ��
    QTimer * setCartoonTimer;
    //�����׳��󶯻����� ��ǰ����
    int potatoCartoonNum;
    //ֲ������
    int myPosX;
    int myPosY;
    //�ж��������Ƿ񳤴�
    bool potatoTNTIsGrowUp;
    //�ж��������Ƿ�ը
    bool potatoTNTIsBang;

    //����
    QGraphicsScene * gameScene;

signals:
    void eatOver();

};

#endif // PLANTS_H
