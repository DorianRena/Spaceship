#ifndef QT_BOSS_H
#define QT_BOSS_H

#include <QRandomGenerator>

#include "Shoot.h"

class GameScene;

class Boss : public QGraphicsPixmapItem{
private:
    GameScene* parent;
    int life;
    int speedX;
    int speedY;
    int intervalshootenemie = 0;
    QList<Shoot*> shoots;

public:
    Boss(QString imageFileName, int life, GameScene* parent);
    virtual ~Boss();

    int getSpeedX();
    int getSpeedY();
    int getLife();
    QList<Shoot*>* getAllShoot();
    int getInterval();

    void setSpeedX(int x);
    void setInterval(int interval);
    void getHit(int damage);

    void shoot();
    void moveAllShoot(int speedY);

    void deleteShoot();
};

#endif //QT_BOSS_H
