#include "Bonus.h"

Bonus::Bonus(QString imageFileName, QString who): QGraphicsPixmapItem(imageFileName){
    this->speedX = QRandomGenerator::global()->bounded(-2,3);
    this->speedY = QRandomGenerator::global()->bounded(1,7);
    this->who = who;
    this->setZValue(1);
}

int Bonus::getSpeedX(){
    return speedX;
}
int Bonus::getSpeedY(){
    return speedY;
}
QString Bonus::getWho(){
    return who;
}

void Bonus::move(int speedx,int speedy){
    QPointF pos = this->pos();
    int newX = pos.x() + speedx;
    int newY = pos.y() + speedy;
    this->setPos(newX, newY);
};
