#ifndef COOLDOWNDARK_H
#define COOLDOWNDARK_H

#include <QGraphicsObject>
#include <QFile>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QTimer>

class coolDownDark : public QGraphicsObject
{
    Q_OBJECT
public:
    coolDownDark(int x,int y,int time);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const override;

private:
    QMediaPlayer * media;
    QTimer * goUp;
    int upTime;

signals:
    void CoolDownEnd();

};

#endif // COOLDOWNDARK_H
