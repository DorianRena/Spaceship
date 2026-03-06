#ifndef QT_ENEMIES_H
#define QT_ENEMIES_H

#include <QRandomGenerator>

#include "Shoot.h"

class GameScene;

class Enemies : public QGraphicsPixmapItem{
private:
    GameScene* parent;
    int pv;
    int speedX;
    int speedY;
    int damage;
    int intervalshootenemie = 0;
    QList<Shoot*> shoots;

public:
    Enemies(QString imageFileName, int pv, int damage, GameScene* parent);
    virtual ~Enemies();

    int getLife();
    int getSpeedX();
    int getSpeedY();
    QList<Shoot*>* getAllShoot();
    int getInterval();

    void setInterval(int interval);
    void getHit(int damage);

    void move(int speedX, int speedY);

    void shoot();
    void moveAllShoot(int speedY);

    void deleteShoot();
};


#endif //QT_ENEMIES_H
