#include "Shoot.h"

//De base les tires sont droit (x=0) mais les boss peuvent tirer en coté
Shoot::Shoot(QString imageFileName, int damage, int x): QGraphicsPixmapItem(QPixmap(imageFileName)){
    this->damage = damage;
    this->speedX = x;
}

int Shoot::getSpeedX(){
    return speedX;
}
int Shoot::getDamageShoot(){
    return damage;
}