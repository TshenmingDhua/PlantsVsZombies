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

    //ֲ�￨����ȴ
    void coolDown();
    //��ȡ����
    void getSunshine();
    //��������Ƿ����
    void checkSunshineEnough();
    //����ֲ��
    void setPlant();

private:
    //���Ʊ��
    int CardId;
    //��ǰֲ����Ҫ����������
    int myPrice;
    //��������
    int sunshineNumber;
    //�жϿ����Ƿ�������ȴ��
    bool isCooldown;
    //�ж��Ƿ����㹻������ѡ��ǰֲ��
    bool isEnoughSunshine;
    //��ȴ��Ӱ��
    coolDownDark * dark;
    //������
    QGraphicsScene * sce;

signals:
    //����item
    void sendNewItem(QGraphicsObject * item);
    //����ֲ��ɹ� ��ȡ�����ź�
    void spendSunshine(int num);
    //��ʱ���͵�ǰ�������
    void sendMousePos(int x,int y);

};

#endif // PLANTSCARD_H
