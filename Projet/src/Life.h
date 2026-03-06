#ifndef QT_LIFE_H
#define QT_LIFE_H

#include <QPixmap>
#include <QGraphicsPixmapItem>

class Life : public QGraphicsPixmapItem {
private :
    int pv;

public :
    Life(QString imageFileName);
    virtual ~Life(){};

    int getLife();
    bool isDead();

    void setHit(int damage);

    void reset();
};


#endif //QT_LIFE_H
