#ifndef QT_SCORE_H
#define QT_SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem{
private:
    int score;

public:
    Score(QString scoretext);
    virtual ~Score(){};

    int getScore();

    void increment();
    void addScore(int add);

    void reset();
};


#endif //QT_SCORE_H
