#ifndef QT_GAMEOVER_H
#define QT_GAMEOVER_H

#include <iostream>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QFontDatabase>
#include <QFile>
#include <QTextStream>

class GameOver : public QGraphicsScene {
Q_OBJECT
private:
    QPixmap background;
    QPushButton* boutton_valider_nom;
    QGraphicsRectItem *Scoreborard;
    QList<QPair<int, QString>> valueSort;
    QList<QPair<int, QString>> tempoValue;
    int score;
    QLineEdit *playerName;
    QList<QGraphicsItem*> allItem;

public:
    GameOver(QObject* parent);
    virtual ~GameOver(){};

    void setScore(int score);
    int playerPos();
    void createScoreboard(QString fileName);
    void addPlayer(QString fileName, QString newName);
    void reset();

    QPair<int, QString> getBestPlayer(QString fileName);


public slots:
    void saveName();
};


#endif //QT_GAMEOVER_H