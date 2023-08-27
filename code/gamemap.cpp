#include "gamemap.h"
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include "plantscard.h"
#include "gamemedia.h"
#include <QVector>
#include "cooldowndark.h"
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "plants.h"
#include "zombies.h"
#include "smallcar.h"
#include <QOpenGLWidget>
#include "spade.h"
#include <QtGlobal>
#include <QPropertyAnimation>
#include <QList>

gameMap::gameMap(QGraphicsView *parent) : QGraphicsView(parent)
{
    //����
//    QOpenGLWidget* openGLWidget = new QOpenGLWidget;
//    this->setViewport(openGLWidget);

    this->setWindowTitle("Plants VS Zombies");
    this->gameScene = new QGraphicsScene;
    this->backgroundItem = new QGraphicsPixmapItem;
    //����ָ��
    //this->setCursor(Qt::BlankCursor);

    //��Ӳݵر���
    this->gameScene->setSceneRect(QRectF(0,0,1400,600));
    this->backgroundItem->setPixmap(QPixmap(":/res/backGround/gameBackground.jpg"));
    this->gameScene->addItem(this->backgroundItem);

    this->setScene(this->gameScene);
    this->setFixedSize(800,602);
    //����ˮƽ�϶���
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->horizontalScrollBar()->setValue(288);

    //��ʾ����label
    this->showSun = new QLabel;
    this->showSun->setText(QString::number(gameMap::SunshineNum));
    this->showSun->setStyleSheet("QLabel {background-color: transparent;}");
    this->showSun->setFont(QFont("Microsoft YaHei",10));
    this->showSun->resize(50,50);
    this->showSun->setAlignment(Qt::AlignHCenter);
    QTimer * updateSun = new QTimer(this);
    connect(updateSun,&QTimer::timeout,this,&gameMap::updateSun);
    updateSun->start(100);

    //��ʾ��ʼվ����ʬ
    this->showBeginStandZombies();

    this->showChoosePlantsWidget();
    this->gameBeginMove();
    //���Դ�����  ����ɾ��-------------------------------------------
    //this->downChooseCard->start(3);
    //------------------------------------------------------------
    //ǿ��ˢ��
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void gameMap::setMouse()
{
    QGraphicsPixmapItem * item = new QGraphicsPixmapItem;
    item->setPixmap(QPixmap(":/res/mouse/mouse.png"));
    this->gameScene->addItem(item);
    item->setZValue(60);
    QTimer * timer = new QTimer;
    connect(timer,&QTimer::timeout,this,[=](){
        item->setPos(Plants::mousePosX - 20,Plants::mousePosY + 29);
    });
    timer->start(6);
}

void gameMap::showChoosePlantsWidget()
{
    this->downChooseCard = new QTimer(this);
    //����ѡ������
    this->chooseCardWidget = new QGraphicsPixmapItem(QPixmap(":/res/backGround/chooseCardBar.png"));
    this->chooseCardWidget->setZValue(1);
    //this->chooseCardWidget->setPos(230,-3);
    this->chooseCardWidget->setPos(230,-89);
    this->gameScene->addItem(chooseCardWidget);
    showSunLabel = this->gameScene->addWidget(this->showSun);
    showSunLabel->setPos(243,60);
    showSunLabel->hide();
    showSunLabel->setZValue(2);

    //���������ƶ�ѡ���ƴ���
    connect(this->downChooseCard,&QTimer::timeout,this,[=](){
        this->chooseCardWidget->setPos(chooseCardWidget->x(),chooseCardWidget->y() + 1);
        if(this->chooseCardWidget->y() >= -3)
        {
            this->downChooseCard->stop();
            this->showSunLabel->show();

            //��ʾֲ�￨��
            this->doShowPlantsCard();
        }
    });
}

void gameMap::updateSun()
{
    //��������Ƿ����仯
    if(this->showSun->text().toInt() == gameMap::SunshineNum)
    {
        return;
    }

    this->showSun->setText(QString::number(gameMap::SunshineNum));
}


void gameMap::gameBeginMove()
{
    this->leftMove = new QTimer(this);
    this->rightMove = new QTimer(this);
    this->horizontalScrollBar()->setValue(0);

    //���ſ�ͷ����
    this->beginChooseCardMedia = new gameMedia(":/res/Media/gameBeginChooseCard.wav");

    connect(this->rightMove,&QTimer::timeout,this,[=](){
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + 1);
        if(this->horizontalScrollBar()->value() >= 600)
        {
            this->rightMove->stop();

            //�ȴ������ ��ͷ�����ƶ�
            QTimer::singleShot(2300,[=](){
                //��ͷ�����ƶ�
                this->leftMove->start(2);
            });
        }
    });
    connect(this->leftMove,&QTimer::timeout,this,[=](){
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - 1);
        if(this->horizontalScrollBar()->value() <= 217)
        {
            this->leftMove->stop();

            //����ѡ��ֲ���
            this->downChooseCard->start(2);

            //��ʾС�Ƴ�
            this->setSmallCar();
            //��ʾ׼����ʼ��Ϸ
            this->showRedReady();
            //���ָ��
            //this->setMouse();
            //����ͷվ����ʬ
            this->deleteBeginZombie();
            //���ò���
            this->setSpade();
            //������Ȼ����
            QTimer * setSunTimer = new QTimer(this);
            connect(setSunTimer,&QTimer::timeout,this,&gameMap::setSunshine);
            setSunTimer->start(13000);

            //��ʼ���ɽ�ʬ
            this->outZombies();
        }
    });

    //���ֵȴ������ ��ʼ�ƶ���ͷ
    QTimer::singleShot(2300,[=](){
        this->rightMove->start(2);
    });
}

void gameMap::doShowPlantsCard()
{
    int id = 1;
    this->cards = {&Id_1,&Id_2,&Id_3,&Id_4,&Id_5,&Id_6};
    for(QVector<PlantsCard**>::iterator it = cards.begin();it!=cards.end();it++)
    {
        *(*it) = new PlantsCard(id,248 + (53 * id),6);
        this->gameScene->addItem((*(*it)));
        id ++;
        //����͸����Ӱitem ������scene��Ϸ������
        connect(*(*it),&PlantsCard::sendNewItem,this,&gameMap::getNewItem);
        //���� ���������źŲ�
        connect(*(*it),&PlantsCard::spendSunshine,this,&gameMap::doSpendSunshine);
    }

    //�����⴫�ݸ�ÿ�ſ�
//    connect(this,&gameMap::sendSunshine,this,[=](int num){
//        for(QVector<PlantsCard**>::iterator it = cards.begin();it!=cards.end();it++)
//        {
//            (*(*it))->getSunshine(num);
//        }
//    });
//    QTimer * send = new QTimer;
//    connect(send,&QTimer::timeout,this,[=](){
//        emit this->sendSunshine(gameMap::SunshineNum);
//    });
//    send->start(10);
}

void gameMap::getNewItem(QGraphicsObject * item)
{
    this->scene()->addItem(item);
}

void gameMap::doSpendSunshine(int num)
{
    gameMap::SunshineNum -= num;
}

void gameMap::showRedReady()
{
    this->showReadyGame = new QGraphicsPixmapItem;
    //��Ч
    gameMedia * ready = new gameMedia(":/res/Media/ReadySetPlant.wav",this);
    this->showReadyGame->setPixmap(QPixmap(":/res/backGround/gameBeginRed/gameBegin-Ready.png"));
    this->showReadyGame->setPos(500,260);
    //��ֹͣ�ʼѡ������
    this->beginChooseCardMedia->stopMedia(true);

    //��ʱ���л�ͼƬ
    QTimer::singleShot(600,[=](){
        this->showReadyGame->setPixmap(QPixmap(":/res/backGround/gameBeginRed/gameBegin-Set.png"));
        this->showReadyGame->setPos(530,260);
    });
    QTimer::singleShot(1200,[=](){
        this->showReadyGame->setPixmap(QPixmap(":/res/backGround/gameBeginRed/gameBegin-Plant.png"));
        this->showReadyGame->setPos(436,260);
    });
    QTimer::singleShot(2000,[=](){
        this->showReadyGame->setPos(0,-300);
        //���Ű�������
        gameMedia * dayMusic = new gameMedia(":/res/Media/pvzDayMusic.wav");
        //����ѭ������
        dayMusic->setForeverPlay(":/res/Media/pvzDayMusic.wav");
    });
    //�����������5
    this->gameScene->addItem(this->showReadyGame);
}

void gameMap::mouseMoveEvent(QMouseEvent *event)
{
    //���������洢��Plants������Ա����
    Plants::mousePosX = event->pos().x() + 190;
    Plants::mousePosY = event->pos().y() - 50;
}

void gameMap::showBeginStandZombies()
{
    Zombies * zombie = new Zombies("normalZombie",true,this->gameScene,this);
    zombie->setPos(1120,110);
    this->zombiesVector.push_back(zombie);
//    zombie = new Zombies("icecreamZombie",false,this->gameScene,this);
//    zombie->setPos(1130,110);
//    this->zombiesVector.push_back(zombie);
    zombie = new Zombies("icecreamZombie",true,this->gameScene,this);
    zombie->setPos(1090,210);
    this->zombiesVector.push_back(zombie);
    zombie = new Zombies("normalZombie",true,this->gameScene,this);
    zombie->setPos(1022,312);
    this->zombiesVector.push_back(zombie);
    zombie = new Zombies("normalZombie",true,this->gameScene,this);
    zombie->setPos(1040,232);
    this->zombiesVector.push_back(zombie);
    zombie = new Zombies("normalZombie",true,this->gameScene,this);
    zombie->setPos(1060,390);
    this->zombiesVector.push_back(zombie);
    zombie = new Zombies("icecreamZombie",true,this->gameScene,this);
    zombie->setPos(1123,250);
    this->zombiesVector.push_back(zombie);
    zombie = new Zombies("normalZombie",true,this->gameScene,this);
    zombie->setPos(1198,230);
    this->zombiesVector.push_back(zombie);
}

void gameMap::deleteBeginZombie()
{
    for(QVector<Zombies *>::iterator it = this->zombiesVector.begin();it!=this->zombiesVector.end();it++)
    {
        delete *it;
    }
}

void gameMap::setSmallCar()
{
    for(int i=0;i<5;i++)
    {
        int num = i * 100;
        smallCar * car = new smallCar(this->gameScene,this);
        car->setPos(179,119 + num);
    }
}

void gameMap::setSpade()
{
    Spade * spade = new Spade(this->gameScene,this);
    QGraphicsPixmapItem * pixmapItem = new QGraphicsPixmapItem;
    pixmapItem->setPixmap(QPixmap(":/res/spade/spadeWidget.png"));
    pixmapItem->setZValue(86);
    this->gameScene->addItem(pixmapItem);
    spade->setPos(776,0);
    pixmapItem->setPos(786,0);
}

void gameMap::setSunshine()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int randomX =   qrand() % 601 + 300;
    int randomY =   qrand() % 401 + 100;

    this->sunshine = new Sunshine(this->gameScene);
    sunshine->natureSunshine(randomX,randomY);
}

void gameMap::outZombies()
{
    //X����ʼΪ 960  YΪ 15 + (n * 100)

    QTimer::singleShot(20000,[=](){
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int randomY = qrand() % 5;

        gameMedia * media = new gameMedia(":/res/Media/zombieComing.mp3",this);
        Zombies * zombie = new Zombies("normalZombie",false,this->gameScene,this);
        zombie->setPos(960,100 * randomY + 15);
    });

    QTimer::singleShot(60000,[=](){
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int randomY = qrand() % 5;

        Zombies * zombie = new Zombies("normalZombie",false,this->gameScene,this);
        zombie->setPos(960,100 * randomY + 15);
        randomY = qrand() % 5;
        zombie = new Zombies("normalZombie",false,this->gameScene,this);
        zombie->setPos(960,100 * randomY + 15);
//        randomY = qrand() % 5;
//        zombie = new Zombies("normalZombie",false,this->gameScene,this);
//        zombie->setPos(960,100 * randomY + 15);
    });

    QTimer::singleShot(95000,[=](){
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int randomY = qrand() % 5;

        Zombies * zombie = new Zombies("normalZombie",false,this->gameScene,this);
        zombie->setPos(960,100 * randomY + 15);
        int randomY2 = qrand() % 5;
        if(randomY2 == randomY)
        {
            randomY = qrand() % 5;
        }
        zombie = new Zombies("icecreamZombie",false,this->gameScene,this);
        zombie->setPos(960,100 * randomY + 15);
    });

    QTimer::singleShot(115000,[=](){
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int randomY = qrand() % 5;

        Zombies * zombie = new Zombies("normalZombie",false,this->gameScene,this);
        zombie->setPos(960,100 * randomY + 15);
    });

    QTimer::singleShot(115000 + 30000,[=](){
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int randomY = qrand() % 5;

        Zombies * zombie = new Zombies("icecreamZombie",false,this->gameScene,this);
        zombie->setPos(960,100 * randomY + 15);
    });

}
int gameMap::SunshineNum = 100;
int gameMap::ZombiesNum = 0;
