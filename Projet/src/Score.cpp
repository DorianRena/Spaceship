#include "Score.h"

Score::Score(QString scoretext): QGraphicsTextItem(scoretext){
    this->setZValue(4);
    this->score = 0;
    this->setDefaultTextColor(QColor(Qt::yellow));
}

int Score::getScore(){
    return score;
}

void Score::increment(){
    this->score++;
    this->setPlainText("Score: " + QString::number(score));
}
void Score::addScore(int add){
    this->score = score + add;
    this->setPlainText("Score: " + QString::number(score));
}

void Score::reset(){
    this->score = 0;
    this->setPlainText("Score: " + QString::number(score));
}