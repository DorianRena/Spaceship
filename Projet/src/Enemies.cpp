#include "Enemies.h"

Enemies::Enemies(QString imageFileName, int pv, int damage, GameScene* parent): QGraphicsPixmapItem(QPixmap(imageFileName)){
    this->parent = parent;
    this->pv = pv;
    this->damage = damage;
    this->speedX = QRandomGenerator::global()->bounded(-2,3);
    this->speedY = QRandomGenerator::global()->bounded(1,6);
    this->setZValue(2);
};
Enemies::~Enemies(){
    this->deleteShoot();
}

int Enemies::getLife(){
    return pv;
}
int Enemies::getSpeedX(){
    return speedX;
}
int Enemies::getSpeedY(){
    return speedY;
}
QList<Shoot*>* Enemies::getAllShoot(){
    return &shoots;
}
int Enemies::getInterval(){
    return intervalshootenemie;
}

void Enemies::setInterval(int interval){
    this->intervalshootenemie=interval;
}
void Enemies::getHit(int damage){
    this->pv = pv-damage;
    if(pv < 1){
        this->setPixmap(QPixmap(":/Projet/img/explosion40.png"));
        this->speedX = 0;
        this->speedY = 0;
        this->setZValue(0);
    }
}

void Enemies::move(int speedX, int speedY){
    QPointF pos = this->pos();

    int newX = pos.x() + speedX;
    int newY = pos.y() + speedY;
    this->setPos(newX, newY);
}

void Enemies::moveAllShoot(int speedY){
    for (auto oneshoot : shoots) {
        oneshoot->setY(oneshoot->y()+speedY);
    }
}

void Enemies::deleteShoot() {
    for(auto shoot : shoots){
        delete shoot;
    }
    shoots.clear();
}