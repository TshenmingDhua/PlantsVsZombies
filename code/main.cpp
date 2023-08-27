#include "mainwidget.h"

#include <QApplication>
#include "gamemap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameMap map;
    map.show();

    return a.exec();
}
