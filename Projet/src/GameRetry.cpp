#include "GameRetry.h"

GameRetry::GameRetry(QObject* parent){
    this->setParent(parent);

    this->background.load(":/Projet/img/Menu.png");
    this->setSceneRect(0, 0, background.width(), background.height());
    this->addPixmap(background);

    this->boutton_rejouer = new QPushButton("Rejouer");
    QGraphicsProxyWidget* widget_rejouer = this->addWidget(boutton_rejouer);
    widget_rejouer->setPos(225, 415);
    widget_rejouer->setMinimumSize(150,30);

    this->boutton_quitter = new QPushButton("Quitter");
    QGraphicsProxyWidget* widget_quitter = this->addWidget(boutton_quitter);
    widget_quitter->setPos(225, 465);
    widget_quitter->setMinimumSize(150,30);

    connect(this->boutton_rejouer,SIGNAL(clicked(bool)),this->parent(),SLOT(restart()));
    connect(this->boutton_quitter,SIGNAL(clicked(bool)),this->parent()->parent(),SLOT(close()));
}