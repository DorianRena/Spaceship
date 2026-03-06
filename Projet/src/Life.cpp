#include "Life.h"

Life::Life(QString imageFileName): QGraphicsPixmapItem(QPixmap(imageFileName)){
    this->setZValue(4);
    this->pv = 6;
}

int Life::getLife(){
    return pv;
}
bool Life::isDead(){
    return pv<1;
}

void Life::setHit(int damage){
    this->pv = pv-damage;
    if(pv > 5){
        this->setPixmap(QPixmap(":/Projet/img/6pv.png"));
        this->pv = 6;
    }else if(pv == 5){
        this->setPixmap(QPixmap(":/Projet/img/5pv.png"));
    }else if(pv == 4){
        this->setPixmap(QPixmap(":/Projet/img/4pv.png"));
    }else if(pv == 3){
        this->setPixmap(QPixmap(":/Projet/img/3pv.png"));
    }else if(pv == 2){
        this->setPixmap(QPixmap(":/Projet/img/2pv.png"));
    }else if(pv == 1){
        this->setPixmap(QPixmap(":/Projet/img/1pv.png"));
    }
}

void Life::reset(){
    this->pv = 6;
    this->setPixmap(QPixmap(":/Projet/img/6pv.png"));
}
