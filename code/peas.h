#ifndef PEAS_H
#define PEAS_H

#include <QObject>
#include <QGraphicsObject>
#include <QTimer>
#include "gamemedia.h"

class Peas : public QGraphicsObject
{
    Q_OBJECT
public:
    Peas(bool isGreen);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;

    void shoot();
    void checkColliding();

private:
    bool isGreenPeas;
    QString filename;
    QTimer * moveTimer;
    gameMedia * media;
    //ÊÇ·ñ´¥·¢delete
    bool isDelete;

signals:
};

#endif // PEAS_H
