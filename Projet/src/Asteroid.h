#ifndef QT_ASTEROID_H
#define QT_ASTEROID_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

class Asteroid : public QGraphicsPixmapItem{
private:
    int speedX = 0;
    int speedY = 0;
    int pv = 0;
    int damage = 0;

public:
    Asteroid(QString imageFileName, int pv, int damage);
    virtual ~Asteroid(){};

    int getLife();
    int getSpeedX();
    int getSpeedY();

    void getHit(int damage);

    void move(int speedx,int speedy);
};

#endif //QT_ASTEROID_H