#include "Boss.h"

Boss::Boss(QString imageFileName, int life, GameScene* parent) : QGraphicsPixmapItem(QPixmap(imageFileName)){
    this->life = life;
    this->speedX = 2;
    this->speedY = 2;
    this->parent = parent;
    this->setZValue(3);
}
Boss::~Boss(){
    this->deleteShoot();
}

int Boss::getSpeedX(){
    return speedX;
}
int Boss::getSpeedY(){
    return speedY;
}
int Boss::getLife(){
    return life;
}
QList<Shoot*>* Boss::getAllShoot(){
    return &shoots;
}
int Boss::getInterval(){
    return intervalshootenemie;
}

void Boss::setSpeedX(int x){
    this->speedX = x;
}
void Boss::setInterval(int interval){
    this->intervalshootenemie=interval;
}
void Boss::getHit(int damage){
    this->life = life-damage;
    if(life < 1){
        this->setPixmap(QPixmap(":/Projet/img/explosion100.png"));
        this->speedY = 0;
        this->setZValue(0);
        this->setPos(this->x()+10,this->y());
    }
}

void Boss::moveAllShoot(int speedY){
    for (auto oneshoot : shoots) {
        oneshoot->setPos(oneshoot->x()+oneshoot->getSpeedX(),oneshoot->y()+speedY);
    }
}

void Boss::deleteShoot() {
    for(auto shoot : shoots){
        delete shoot;
    }
    shoots.clear();
}