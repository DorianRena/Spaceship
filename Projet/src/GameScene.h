#ifndef QT_GAMESCENE_H
#define QT_GAMESCENE_H

#include <QApplication>
#include <QPixmap>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QFile>
#include <QSlider>

#include "SpaceShip.h"
#include "Life.h"
#include "Enemies.h"
#include "Asteroid.h"
#include "Bonus.h"
#include "Score.h"
#include "Boss.h"
#include "Musique.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT
private:
    QPixmap background;
    Score* score;

    QTimer* timer;
    QPointF centerPoint;
    QList<int> keyPressed;

    SpaceShip* ship;
    Life* life;
    QList<Enemies*> enemies;
    QList<Asteroid*> asteroids;
    QList<Bonus*> bonus;
    QList<Boss*> bosses;

    QGraphicsPixmapItem* pause;
    int intervalpause = 0;
    bool arePause = false;

    QGraphicsPixmapItem* nbombe_img;
    QGraphicsTextItem* nbombe;
    int nbBombe = 0;

    int speedGame = 2;
    int intervalshoot = 0;
    int intervalbombe = 0;

    Musique* musique;
    QGraphicsPixmapItem* volume;
    QSlider* slider;
    //QGraphicsProxyWidget* Widget_slider;

    QSize viewSize;

    int iter_in_pause = 0;
    int ecart_fullscreen = 0;

public:
    GameScene(QObject* parent = nullptr);
    virtual ~GameScene();

    QTimer* getTimer(){return timer;};
    QPointF* getCenterPoint(){return &centerPoint;};

    void keyPressEvent(QKeyEvent* event);
    void checkPause();
    void checkKeys();
    void keyReleaseEvent(QKeyEvent* event);

    void bombe();

    void createEnemies(int al);
    void createAsteroids(int al);
    void createBonus();
    void createBoss();

    void moveAll();

    void moveAllEnemies();
    void moveAllAsteroids();
    void moveAllBonus();
    void moveAllBoss();

    void collision();

    void deleteAll();
    void reset();

    Musique* getMusique(){return musique;};
    QGraphicsPixmapItem* getVolume(){return volume;};
    QSlider* getSlider(){return slider;};
    //QGraphicsProxyWidget* getWidget_slider(){return Widget_slider;};


signals:
    void dead(int score);
public slots:
    void update();
    void checkdead();
};


#endif //QT_GAMESCENE_H
