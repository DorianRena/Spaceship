#ifndef QT_BONUSPV_H
#define QT_BONUSPV_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

class Bonus : public QGraphicsPixmapItem {
private:
    int speedX = 0;
    int speedY = 0;
    QString who;

public:
    Bonus(QString imageFileName, QString who);
    virtual ~Bonus(){};

    int getSpeedX();
    int getSpeedY();
    QString getWho();

    void move(int speedx,int speedy);
};


#endif //QT_BONUSPV_H
