#ifndef QT_SHOOT_H
#define QT_SHOOT_H

#include <QPixmap>
#include <QGraphicsPixmapItem>

//Classe des shoots du spaceship/énnemies/boss
class Shoot : public QGraphicsPixmapItem{
private:
    int damage = 0;
    int speedX = 0;

public:
    Shoot(QString imageFileName, int damage, int x=0);
    virtual ~Shoot(){};

    int getSpeedX();
    int getDamageShoot();
};


#endif //QT_SHOOT_H
