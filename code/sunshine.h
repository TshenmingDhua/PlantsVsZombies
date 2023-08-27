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

    //���¶���
    void loadCartoon();
    //�ƶ�����������
    void goMove();
    //��ʱ�䲻�ռ��Զ���ʧ
    void clearMe();
    //��Ȼ�������⶯��
    void natureSunshine(int x,int y);

private:
    QString pixAddr;
    //��ǰ��������
    int pixNum;

    //Ŀ���̫������
    int bigsunX;
    int bigsunY;
    QTimer * move;
    //�Ƿ��Ѿ������
    bool isMove;
    //������ʱ��
    QTimer * cartoonTimer;
    //��Ȼ���⶯����
    QPropertyAnimation * natureAnimation;

signals:
    //��������
    void addSunNum();

};

#endif // SUNSHINE_H
