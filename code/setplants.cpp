#include "setplants.h"
#include <QDebug>

setPlants::setPlants()
{

}

QVector<int> setPlants::setPlantInSquare(int x,int y)
{
    QVector<int> vector;
    int Xnum = x - 250;
    int Ynum = y - 80;

    Xnum /= 80;
    Ynum /= 100;

    int num = 1;
    for(QVector<int>::iterator it = setPlants::isSetPlant.begin();it!=setPlants::isSetPlant.end();it++)
    {
        if(num == 1)
        {
            num = 2;
            if(*it == Xnum && *(it+1) == Ynum)
            {
                vector = {-1,-1};
                return vector;
            }
        }
        else
        {
            num = 1;
        }
    }
    setPlants::isSetPlant.push_back(Xnum);
    setPlants::isSetPlant.push_back(Ynum);

    Xnum *= 80;
    Ynum *= 100;
    int posX = 260 + Xnum;
    int posY = 90 + Ynum;

    vector = {posX,posY};

//    qDebug()<<"---------";
//    for(QVector<int>::iterator it = setPlants::isSetPlant.begin();it!=setPlants::isSetPlant.end();it++)
//    {
//        qDebug()<<*it;
//    }
//    qDebug()<<"---------";

    return vector;
}

void setPlants::deletePos(int x, int y)
{
    QVector<int> vector;
    int Xnum = x - 250;
    int Ynum = y - 80;

    Xnum /= 80;
    Ynum /= 100;

    int num = 1;
    QVector<int>::iterator eraseIt = setPlants::isSetPlant.end();
    for(QVector<int>::iterator it = setPlants::isSetPlant.begin();it!=setPlants::isSetPlant.end();it++)
    {
        if(num == 1 && *it == Xnum && *(it + 1) == Ynum)
        {
            eraseIt = it;
        }
    }
    if(eraseIt == setPlants::isSetPlant.end() || eraseIt + 1 == setPlants::isSetPlant.end())
    {
        return;
    }

    setPlants::isSetPlant.erase(eraseIt,eraseIt + 2);

//        qDebug()<<"---------";
//        for(QVector<int>::iterator it = setPlants::isSetPlant.begin();it!=setPlants::isSetPlant.end();it++)
//        {
//            qDebug()<<*it;
//        }
//        qDebug()<<"---------";
}

QVector<int> setPlants::isSetPlant;
