#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QObject>

class Zombie : public QObject
{
    Q_OBJECT
public:
    explicit Zombie(QObject *parent = nullptr);

signals:

};

#endif // ZOMBIE_H
