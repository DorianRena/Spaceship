#include "Menu.h"

Menu::Menu(QObject* parent){
    this->setParent(parent);

    this->background.load(":/Projet/img/Menu.png");
    this->setSceneRect(0, 0, background.width(), background.height());
    this->addPixmap(background);

    volume = new QGraphicsPixmapItem(QPixmap(":/Projet/img/volume.png"));
    this->addItem(volume);
    volume->setPos(565, 10);

    slider = new QSlider();
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setValue(50);
    slider->move(570, 40);
    slider->setStyleSheet("QSlider { background: transparent; }"
                          "QSlider::handle:vertical { background: rgb(207, 144, 218); }");
    QGraphicsProxyWidget* Widget_slider = this->addWidget(slider);

    connect(slider, &QSlider::valueChanged, [this](float value){
        this->scene->getMusique()->setVolumeMusic(value);
    });



    this->boutton_jouer = new QPushButton("Jouer");
    this->boutton_jouer->setStyleSheet(
            "QPushButton {"
            "   background-color: transparent;"
            "   border: none;"
            "   color: rgb(207, 144, 218);"
            "   font-weight: bold;"
            "   font-family: '"+QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/Projet/other/ArcadeClassic.ttf")).at(0)+"';"
                                                                                                                                                    "   font-size: 30px;"
                                                                                                                                                    "}"
                                                                                                                                                    "QPushButton:hover {"
                                                                                                                                                    "   text-decoration: underline;"
                                                                                                                                                    "   color: rgb(60, 0, 90);"
                                                                                                                                                    "}"
    );
    QGraphicsProxyWidget* widget_jouer = this->addWidget(boutton_jouer);
    widget_jouer->setPos(225, 355);
    widget_jouer->setMinimumSize(150,30);

    this->boutton_quitter = new QPushButton("Quitter");
    this->boutton_quitter->setStyleSheet(
            "QPushButton {"
            "   background-color: transparent;"
            "   border: none;"
            "   color: rgb(207, 144, 218);"
            "   font-weight: bold;"
            "   font-family: '"+QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/Projet/other/ArcadeClassic.ttf")).at(0)+"';"
                                                                                                                                                    "   font-size: 30px;"
                                                                                                                                                    "}"
                                                                                                                                                    "QPushButton:hover {"
                                                                                                                                                    "   text-decoration: underline;"
                                                                                                                                                    "   color: rgb(60, 0, 90);"
                                                                                                                                                    "}"
    );
    QGraphicsProxyWidget* widget_quitter = this->addWidget(boutton_quitter);
    widget_quitter->setPos(225, 415);
    widget_quitter->setMinimumSize(150,30);

    this->scene = new GameScene(this);
    this->gameover_scene = new GameOver(this);

    bestPlayerInfo = new QGraphicsTextItem("");
    this->addItem(bestPlayerInfo);
    printBestPlayer();

    QGraphicsTextItem* credit_Music = new QGraphicsTextItem("Musique : Spaceship de Trei Degete (Squeezie)");
    credit_Music->setDefaultTextColor(Qt::white);
    QFont font("QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(\":/Projet/other/ArcadeClassic.ttf\")).at(0)", 8);
    credit_Music->setFont(font);
    credit_Music->setPos(334, 584);
    this->addItem(credit_Music);



    connect(this->boutton_jouer,SIGNAL(clicked(bool)),this,SLOT(start()));
    connect(this->boutton_quitter,SIGNAL(clicked(bool)),this->parent(),SLOT(close()));
}
Menu::~Menu(){
    delete gameover_scene;
    delete scene;
}

void Menu::start(){
    this->scene->reset();
    this->scene->getTimer()->start(30);
    this->views()[0]->setScene(this->scene);
}
void Menu::menuGameOver(int score){
    this->scene->getTimer()->stop();
    this->gameover_scene->setScore(score);
    this->slider->setValue(static_cast<int>(this->scene->getMusique()->getVolume()));
    this->scene->views()[0]->setScene(this->gameover_scene);
}
void Menu::menuGameRetry(){
    this->boutton_jouer->setText("Rejouer");
    printBestPlayer();
    this->gameover_scene->views()[0]->setScene(this);
}

void Menu::printBestPlayer(){
    QFile localFile("Score.csv");
    if (localFile.exists()) {
        bestPlayer = this->gameover_scene->getBestPlayer("Score.csv");
    } else {
        bestPlayer = this->gameover_scene->getBestPlayer(":/Projet/other/Score.csv");
    }
    bestPlayerInfo->setPlainText("Meilleur Joueur : "+bestPlayer.second+" avec "+QString::number(bestPlayer.first)+" points");
    bestPlayerInfo->setDefaultTextColor(Qt::yellow);
    QFont font("QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(\":/Projet/other/ArcadeClassic.ttf\")).at(0)", 10);
    bestPlayerInfo->setFont(font);
    bestPlayerInfo->setPos(40, 260);
}