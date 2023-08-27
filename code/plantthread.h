#ifndef PLANTTHREAD_H
#define PLANTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QPixmap>

class plantThread : public QThread
{
    Q_OBJECT
public:
    plantThread();


//    void startThread();

    void startWork();
    void startTime();

    void setPos(int x);

protected:
    void run() override;

private:
    int posX,posY;


    QString address;
    QThread * thread;
    int picNum = 1;
    QTimer * timer;

signals:
    void sendPos(int x);

};


//class Worker : public QObject
//{
//    Q_OBJECT
//public:
//    Worker()
//    {
//        this->m_timer = new QTimer(this);
//        connect(m_timer, &QTimer::timeout, this, &Worker::doWork);
//    }

//    void start()
//    {
//        m_timer->start(100);
//    }
//     void doWork()
//     {
//                    QString add = ":/res/plants/sunflower/sunflower";
//                    add = add + QString::number(this->picNum) + ".png";
//                    this->picNum++;
//                    if (this->picNum == 28)
//                    {
//                        this->picNum = 1;
//                    }
//                    emit this->sendAddr(add);
//     }
//signals:
//    void sendAddr(QString addr);

//private:
//    int picNum = 1;
//    QTimer * m_timer;
//};

#endif // PLANTTHREAD_H
