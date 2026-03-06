#include "SpaceShip.h"

SpaceShip::SpaceShip(QString imageFileName,GameScene* parent): QGraphicsPixmapItem(QPixmap(imageFileName)){
    this->parent = parent;
    this->setZValue(4);
}
SpaceShip::~SpaceShip(){
    this->deleteShoot();
}

QList<Shoot*>* SpaceShip::getAllShoot(){
    return &shoots;
}
int SpaceShip::getSpeed(){
    return speed;
}

void SpaceShip::upSpeed(){
    this->speed++;
}

void SpaceShip::moveRight() {
    QPointF pos = this->pos();

    int newX = pos.x() + speed;
    if (newX > 500) {
        newX = 500;
    }
    this->setPos(newX, pos.y());
}
void SpaceShip::moveLeft() {
    QPointF pos = this->pos();

    int newX = pos.x() - speed;
    if (newX < 0) {
        newX = 0;
    }
    this->setPos(newX, pos.y());
}
void SpaceShip::moveAllShoot(int speedY){
    for (auto oneshoot : shoots) {
        oneshoot->setY(oneshoot->y()+speedY);
    }
}

void SpaceShip::deleteShoot() {
    for (auto oneshoot : shoots) {
        delete oneshoot;
    }
    shoots.clear();
}
void SpaceShip::reset(){
    this->speed = 5;
}