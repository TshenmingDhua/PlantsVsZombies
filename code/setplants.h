#ifndef SETPLANTS_H
#define SETPLANTS_H

#include <QObject>
#include <QVector>
#include <QMap>

class setPlants : public QObject
{
    Q_OBJECT
public:
    setPlants();

    static QVector<int> setPlantInSquare(int x,int y);
    static void deletePos(int x,int y);

private:
    static QVector<int> isSetPlant;

signals:

};

#endif // SETPLANTS_H
