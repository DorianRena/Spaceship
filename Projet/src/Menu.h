#ifndef QT_MENU_H
#define QT_MENU_H

#include <QApplication>
#include <QMainWindow>
#include <QSlider>

#include "GameOver.h"
#include "GameScene.h"

class Menu : public QGraphicsScene {
Q_OBJECT
private:
    QPixmap background;
    QPushButton* boutton_jouer;
    QPushButton* boutton_quitter;
    QPair<int, QString> bestPlayer;
    QGraphicsTextItem *bestPlayerInfo;

    GameScene* scene;
    GameOver* gameover_scene;

    QGraphicsPixmapItem* volume;
    QSlider* slider;

public:
    Menu(QObject* parent);
    virtual ~Menu();

    void printBestPlayer();

public slots:
    void start();
    void menuGameOver(int score);
    void menuGameRetry();

};


#endif //QT_MENU_H