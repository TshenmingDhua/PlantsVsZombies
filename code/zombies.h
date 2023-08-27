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

    //���ý�ʬ����
    void loadZombieCartoon();
    //���ý�ʬ����ͼƬ����
    void setCartoonPixmap();
    //��ʬ����
    void goWalk();
    //��ʬ��ֲ��
    void doEating();
    //����ֲ��
    void eatOver();
    //��������ֵ
    void lessHealth();
    //��������
    void dead();
    //����������
    void beIce();

    //�Ƿ��Ѿ�����
    bool isDead;
    //�Ƿ񱻱���
    bool isBeIce;

private:
    QString m_Name;
    bool isStand;
    //�ж��Ƿ����ڳ�ֲ��
    bool isEating;

    //��ǰ��ʬͼƬ·��
    QString zombiePixmap;
    //��ʬ�����л��ٶ�
    int cartoonSpeed;
    //��ǰ��ʬ����ͼƬ���� �ڼ���
    int cartoonNum;
    //�ܹ���ʬ����ͼƬ����
    int allCartoonNum;
    //��ʬ��ֲ�ﶯ������
    int allEatCartoonNum;

    //��ʬ����ֵ ��ͨ10��·��30
    int health;

    //��·��ʱ��
    QTimer * walkTimer;
    //��ֲ����Ƶ
    gameMedia * eatMedia;

    //�Ѿ�delete
    bool isDelete;
    //��¼������������ ��ǰ����
    int deadCartoonNum;
    //������ʱ��
    QTimer * cartoonTimer;

signals:

};

#endif // ZOMBIES_H
