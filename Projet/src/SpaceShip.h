#ifndef QT_SPACESHIP_H
#define QT_SPACESHIP_H
#include <iostream>


#include <QGraphicsScene>
#include <QPointF>

#include "Shoot.h"

class GameScene;
// Classe du vaisseau principal qui utilise sa classe parent pour ajouter les tires dans la scene et voir la dimension de la vue
class SpaceShip : public QGraphicsPixmapItem {
private:
    GameScene* parent;
    int speed=5;
    QList<Shoot*> shoots;

public:
    SpaceShip(QString imageFileName,GameScene* parent);
    virtual ~SpaceShip();

    QList<Shoot*>* getAllShoot();
    int getSpeed();

    void upSpeed();

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void shoot();
    void moveAllShoot(int speedY);

    void deleteShoot();
    void reset();
};

#endif //QT_SPACESHIP_H
