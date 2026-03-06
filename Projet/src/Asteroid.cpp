#include "Asteroid.h"

Asteroid::Asteroid(QString imageFileName, int pv, int damage): QGraphicsPixmapItem(imageFileName){
    this->pv = pv;
    this->damage = damage;
    this->speedX = QRandomGenerator::global()->bounded(-2,3);
    this->speedY = QRandomGenerator::global()->bounded(1,7);
    this->setZValue(3);
};

int Asteroid::getLife(){
    return pv;
}
int Asteroid::getSpeedX(){
    return speedX;
}
int Asteroid::getSpeedY(){
    return speedY;
}

void Asteroid::getHit(int damage){
    this->pv = pv-damage;
    if(pv == 3){
        this->setPixmap(QPixmap(":Projet/img/Astéro80,65.png"));
    }else if(pv == 2){
        this->setPixmap(QPixmap(":Projet/img/Astéro60,55.png"));
    }else if(pv == 1){
        this->setPixmap(QPixmap(":Projet/img/Astéro40,45.png"));
    }else if(pv < 1){
        this->setPixmap(QPixmap(":/Projet/img/explosion40.png"));
        this->speedX = 0;
        this->speedY = 0;
        this->setZValue(0);
    }
}

void Asteroid::move(int speedx,int speedy){
    QPointF pos = this->pos();
    int newX = pos.x() + speedx;
    int newY = pos.y() + speedy;
    this->setPos(newX, newY);
};