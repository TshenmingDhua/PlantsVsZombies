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
    //测试
//    QOpenGLWidget* openGLWidget = new QOpenGLWidget;
//    this->setViewport(openGLWidget);

    this->setWindowTitle("Plants VS Zombies");
    this->gameScene = new QGraphicsScene;
    this->backgroundItem = new QGraphicsPixmapItem;
    //隐藏指针
    //this->setCursor(Qt::BlankCursor);

    //添加草地背景
    this->gameScene->setSceneRect(QRectF(0,0,1400,600));
    this->backgroundItem->setPixmap(QPixmap(":/res/backGround/gameBackground.jpg"));
    this->gameScene->addItem(this->backgroundItem);

    this->setScene(this->gameScene);
    this->setFixedSize(800,602);
    //隐藏水平拖动条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->horizontalScrollBar()->setValue(288);

    //显示阳光label
    this->showSun = new QLabel;
    this->showSun->setText(QString::number(gameMap::SunshineNum));
    this->showSun->setStyleSheet("QLabel {background-color: transparent;}");
    this->showSun->setFont(QFont("Microsoft YaHei",10));
    this->showSun->resize(50,50);
    this->showSun->setAlignment(Qt::AlignHCenter);
    QTimer * updateSun = new QTimer(this);
    connect(updateSun,&QTimer::timeout,this,&gameMap::updateSun);
    updateSun->start(100);

    //显示初始站立僵尸
    this->showBeginStandZombies();

    this->showChoosePlantsWidget();
    this->gameBeginMove();
    //测试代码用  编译删除-------------------------------------------
    //this->downChooseCard->start(3);
    //------------------------------------------------------------
    //强制刷新
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
    //创建选卡窗口
    this->chooseCardWidget = new QGraphicsPixmapItem(QPixmap(":/res/backGround/chooseCardBar.png"));
    this->chooseCardWidget->setZValue(1);
    //this->chooseCardWidget->setPos(230,-3);
    this->chooseCardWidget->setPos(230,-89);
    this->gameScene->addItem(chooseCardWidget);
    showSunLabel = this->gameScene->addWidget(this->showSun);
    showSunLabel->setPos(243,60);
    showSunLabel->hide();
    showSunLabel->setZValue(2);

    //连接向下移动选择卡牌窗口
    connect(this->downChooseCard,&QTimer::timeout,this,[=](){
        this->chooseCardWidget->setPos(chooseCardWidget->x(),chooseCardWidget->y() + 1);
        if(this->chooseCardWidget->y() >= -3)
        {
            this->downChooseCard->stop();
            this->showSunLabel->show();

            //显示植物卡牌
            this->doShowPlantsCard();
        }
    });
}

void gameMap::updateSun()
{
    //检测阳光是否发生变化
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

    //播放开头音乐
    this->beginChooseCardMedia = new gameMedia(":/res/Media/gameBeginChooseCard.wav");

    connect(this->rightMove,&QTimer::timeout,this,[=](){
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + 1);
        if(this->horizontalScrollBar()->value() >= 600)
        {
            this->rightMove->stop();

            //等待两秒后 镜头向左移动
            QTimer::singleShot(2300,[=](){
                //镜头向左移动
                this->leftMove->start(2);
            });
        }
    });
    connect(this->leftMove,&QTimer::timeout,this,[=](){
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - 1);
        if(this->horizontalScrollBar()->value() <= 217)
        {
            this->leftMove->stop();

            //出现选择植物框
            this->downChooseCard->start(2);

            //显示小推车
            this->setSmallCar();
            //显示准备开始游戏
            this->showRedReady();
            //鼠标指针
            //this->setMouse();
            //清理开头站立僵尸
            this->deleteBeginZombie();
            //设置铲子
            this->setSpade();
            //设置自然阳光
            QTimer * setSunTimer = new QTimer(this);
            connect(setSunTimer,&QTimer::timeout,this,&gameMap::setSunshine);
            setSunTimer->start(13000);

            //开始生成僵尸
            this->outZombies();
        }
    });

    //开局等待两秒后 开始移动镜头
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
        //将半透明阴影item 发送至scene游戏场景中
        connect(*(*it),&PlantsCard::sendNewItem,this,&gameMap::getNewItem);
        //连接 花费阳光信号槽
        connect(*(*it),&PlantsCard::spendSunshine,this,&gameMap::doSpendSunshine);
    }

    //将阳光传递给每张卡
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
    //音效
    gameMedia * ready = new gameMedia(":/res/Media/ReadySetPlant.wav",this);
    this->showReadyGame->setPixmap(QPixmap(":/res/backGround/gameBeginRed/gameBegin-Ready.png"));
    this->showReadyGame->setPos(500,260);
    //逐渐停止最开始选卡音乐
    this->beginChooseCardMedia->stopMedia(true);

    //计时器切换图片
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
        //播放白天音乐
        gameMedia * dayMusic = new gameMedia(":/res/Media/pvzDayMusic.wav");
        //设置循环播放
        dayMusic->setForeverPlay(":/res/Media/pvzDayMusic.wav");
    });
    //添加至场景中5
    this->gameScene->addItem(this->showReadyGame);
}

void gameMap::mouseMoveEvent(QMouseEvent *event)
{
    //将鼠标坐标存储至Plants公共成员变量
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
    //X轴起始为 960  Y为 15 + (n * 100)

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
