#ifndef QT_GAMERETRY_H
#define QT_GAMERETRY_H

#include <iostream>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

class GameRetry : public QGraphicsScene {
Q_OBJECT
private:
    QPixmap background;
    QPushButton* boutton_rejouer;
    QPushButton* boutton_quitter;

public:
    GameRetry(QObject* parent);
};

#endif //QT_GAMERETRY_H
