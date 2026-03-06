#include "GameScene.h"
#include <QSpacerItem>

GameScene::GameScene(QObject* parent){
    this->setParent(parent);

    this->musique = new Musique(parent);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->background.load(":/Projet/img/Background.png");
    this->setSceneRect(0, 0, background.width(), background.height());
    this->addPixmap(background);

    this->centerPoint =  QPointF(300,800);

    this->ship = new SpaceShip(":/Projet/img/SpaceShip.png",this);
    this->addItem(ship);
    this->ship->setPos(250,900);

    this->life = new Life(":/Projet/img/6pv.png");
    this->addItem(life);
    this->life->setPos(centerPoint.x() + 200, centerPoint.y() + 280);

    this->score = new Score("Score: 0");
    this->addItem(score);
    this->score->setPos(centerPoint.x() - 300, centerPoint.y() - 300);

    this->pause = new QGraphicsPixmapItem(QPixmap(":/Projet/img/pause.png"));
    this->addItem(pause);
    this->pause->setZValue(5);

    this->nbombe_img = new QGraphicsPixmapItem(QPixmap(":/Projet/img/bombe_img.png"));
    this->addItem(nbombe_img);
    this->nbombe_img->setPos(centerPoint.x() - 295, centerPoint.y() + 295);
    this->nbombe_img->setZValue(5);

    this->nbombe = new QGraphicsTextItem("x0");
    this->addItem(nbombe);
    this->nbombe->setDefaultTextColor(QColor(0,100,170));
    QFont font = nbombe->font();
    font.setPointSize(12);
    this->nbombe->setFont(font);
    this->nbombe->setPos(centerPoint.x() - 280, centerPoint.y() + 292);
    this->nbombe->setZValue(5);

    this->volume = new QGraphicsPixmapItem(QPixmap(":/Projet/img/volume.png"));
    this->addItem(volume);
    this->volume->setZValue(5);

    this->slider = new QSlider();
    this->slider->setMinimum(0);
    this->slider->setMaximum(100);
    this->slider->setValue(50);
    this->slider->setStyleSheet("QSlider { background: transparent; }"
                          "QSlider::handle:vertical { background: rgb(207, 144, 218); }");
    QGraphicsProxyWidget* Widget_slider = this->addWidget(slider);
    Widget_slider->setZValue(5);

    QGraphicsRectItem* rectangle1 = new QGraphicsRectItem();
    rectangle1->setRect(-300, 0, 300, this->height());
    rectangle1->setBrush(QColor(Qt::white));
    QPen pen1(Qt::NoPen);
    rectangle1->setPen(pen1);
    this->addItem(rectangle1);
    rectangle1->setZValue(10);

    QGraphicsRectItem* rectangle2 = new QGraphicsRectItem();
    rectangle2->setRect(600, 0, 300, this->height());
    rectangle2->setBrush(QColor(Qt::white));
    QPen pen2(Qt::NoPen);
    rectangle2->setPen(pen2);
    this->addItem(rectangle2);
    rectangle2->setZValue(10);


    connect(slider, &QSlider::valueChanged, [this](float value){
        this->getMusique()->setVolumeMusic(value);
    });

    connect(this,SIGNAL(dead(int)),this->parent(),SLOT(menuGameOver(int)));
}
GameScene::~GameScene(){
    this->setParent(nullptr);
    this->timer->setParent(nullptr);
    delete this->timer;
    delete this->ship;
    delete this->life;
    delete this->score;
    for (auto enemie : enemies){
        delete enemie;
    }
    enemies.clear();
    for (auto asteroid : asteroids){
        delete asteroid;
    }
    enemies.clear();
}

// Signaux
void GameScene::checkdead(){
    emit dead(score->getScore());
}

// Appel toutes les 30ms
void GameScene::update() {
    this->checkPause();
    viewSize = this->views()[0]->viewport()->size();
    this->views().first()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int yOffset = (viewSize.height()*5/11) + ((viewSize.height()-centerPoint.x()-280)/23);
    int yOffset_pause =  (viewSize.height()*11/22) +((viewSize.height()-centerPoint.x()-280)*125/248)-53;

    if(!arePause){
        this->deleteAll();
        this->collision();

        this->score->increment();
        this->nbombe->setPlainText("x" + QString::number(nbBombe));
        this->createBonus();
        this->createBoss();
        if(bosses.isEmpty() or bosses[0]->getLife()<1){
            this->createEnemies(speedGame-2);
            this->createAsteroids(speedGame-2);
        }else{
            this->createAsteroids(-5);
        }

        int newY = centerPoint.y() - speedGame;
        if (newY < 800) {
            newY = newY+400;
            this->moveAll();
        }
        this->centerPoint.setY(newY);
        this->views()[0]->centerOn(this->centerPoint);
        if(ship->y()> centerPoint.y() + yOffset-50){
            this->ship->setY(centerPoint.y() + yOffset -55);
        }
        else{
            this->ship->setY(ship->y() - speedGame);
        }
        this->life->setY(centerPoint.y() + yOffset - speedGame);
        this->nbombe_img->setY(centerPoint.y() + yOffset - speedGame + 5);
        this->nbombe->setY(centerPoint.y() + yOffset - speedGame + 2);

        this->score->setY(centerPoint.y() - viewSize.height()/2 - speedGame);
        this->ship->moveAllShoot(- (speedGame*4));
        this->moveAllEnemies();
        this->moveAllAsteroids();
        this->moveAllBonus();
        this->moveAllBoss();

        this->checkKeys();

        if(life->isDead()){
            this->checkdead();
        }
    }
    else{
        iter_in_pause++;
        if(viewSize.height()>= 985 && iter_in_pause ==1){
            ecart_fullscreen = 181;
        }
        if(ship->y()> centerPoint.y() + yOffset_pause-50-ecart_fullscreen){
            this->ship->setY(centerPoint.y() + yOffset_pause -55-ecart_fullscreen);
        }
        else{
            this->ship->setY(ship->y());
        }
        this->life->setY( centerPoint.y() +yOffset_pause -ecart_fullscreen);
        this->nbombe_img->setY(centerPoint.y() + yOffset_pause + 5-ecart_fullscreen);
        this->nbombe->setY(centerPoint.y() + yOffset_pause  + 2-ecart_fullscreen);
        this->pause->setPos(centerPoint.x() - 40, centerPoint.y() -220 +yOffset_pause*6/11 -ecart_fullscreen);
    }
}

// Vérification touches
void GameScene::keyPressEvent(QKeyEvent* event){
    this->keyPressed.push_back(event->key());
}
void GameScene::checkPause() {
    intervalpause++;
    this->pause->setVisible(arePause);
    if(keyPressed.contains(Qt::Key_P) and (intervalpause>10)) {
        this->intervalpause = 0;
        if(arePause){
            volume->setPos(0,0);
            slider->move(0,0);
            this->arePause = false;
        }else{

            this->arePause = true;
            this->pause->setPos(centerPoint.x() - 40, centerPoint.y() - 40);
            iter_in_pause = 0;
            ecart_fullscreen = 0;
            volume->setPos(centerPoint.x()+265, centerPoint.y()-viewSize.height()/2);
            slider->move(centerPoint.x()+270, centerPoint.y()-viewSize.height()/2 +30);
        }
    }
}
void GameScene::checkKeys(){
    if(keyPressed.contains(Qt::Key_Up)) {
        this->ship->moveUp();
    }
    if(keyPressed.contains(Qt::Key_Down)) {
        this->ship->moveDown();
    }
    if(keyPressed.contains(Qt::Key_Right)) {
        this->ship->moveRight();
    }
    if(keyPressed.contains(Qt::Key_Left)) {
        this->ship->moveLeft();
    }
    intervalshoot++;
    if(keyPressed.contains(Qt::Key_Space) and (intervalshoot>10)) {
        this->intervalshoot = 0;
        this->ship->shoot();
    }
    intervalbombe++;
    if(keyPressed.contains(Qt::Key_B) and (intervalbombe>10) and nbBombe>0) {
        this->intervalbombe = 0;
        this->nbBombe--;
        this->bombe();
    }
}
void GameScene::keyReleaseEvent(QKeyEvent* event){
    this->keyPressed.removeOne(event->key());
}

// Si on utilise la bombe
void GameScene::bombe(){
    for (auto enemie : enemies){
        enemie->getHit(10);
        enemie->deleteShoot();
        this->score->addScore(500);
    }
    for (auto asteroid : asteroids){
        asteroid->getHit(10);
        this->score->addScore(500);
    }
    for (auto bo : bosses){
        bo->getHit(10);
        bo->deleteShoot();
        this->score->addScore(500);
    }
}

// Création des items
void GameScene::createEnemies(int al){
    int alea = QRandomGenerator::global()->bounded(0,40-2*al);
    if(alea==0){
        int pv = QRandomGenerator::global()->bounded(1,3);
        QString chemin("");
        if(pv==1){
            chemin = QString(":Projet/img/Enemie1.png");
        }else{
            chemin = QString(":Projet/img/Enemie2.png");
        }
        Enemies* enemie = new Enemies(chemin, pv,1,this);
        this->addItem(enemie);
        int x;
        if(enemie->getSpeedX()<0){
            x = QRandomGenerator::global()->bounded(200,600);
        }else if(enemie->getSpeedX()>0){
            x = QRandomGenerator::global()->bounded(0,400);
        }else{
            x = QRandomGenerator::global()->bounded(25,575);
        }
        enemie->setPos(x,200);
        this->enemies.push_back(enemie);
    }
}
void GameScene::createAsteroids(int al) {
    int alea = QRandomGenerator::global()->bounded(0,25-2*al);
    if(alea==0){
        int pv = QRandomGenerator::global()->bounded(1,5);
        QString chemin("");
        if(pv==4){
            chemin = QString(":Projet/img/Astéro110,100.png");
            pv = 5;
        }else if(pv==3){
            chemin = QString(":Projet/img/Astéro80,65.png");
        }else if(pv==2){
            chemin = QString(":Projet/img/Astéro60,55.png");
        }else{
            chemin = QString(":Projet/img/Astéro40,45.png");
        }
        Asteroid* asteroid = new Asteroid(chemin, pv,1);
        this->addItem(asteroid);
        int x;
        if(asteroid->getSpeedX()<0){
            x = QRandomGenerator::global()->bounded(200,600);
        }else if(asteroid->getSpeedX()>0){
            x = QRandomGenerator::global()->bounded(0,400);
        }else{
            x = QRandomGenerator::global()->bounded(25,575);
        }        asteroid->setPos(x,200);
        this->asteroids.push_back(asteroid);
    }
}
void GameScene::createBonus() {
    int alea = QRandomGenerator::global()->bounded(0,600);
    if(alea==0){
        QString chemin("");
        QString who("");
        alea = QRandomGenerator::global()->bounded(0,5);
        if((alea==0 or alea==1) and life->getLife()<6){
            chemin = QString(":Projet/img/heal.png");
            who = QString("heal");
        }else{
            chemin = QString(":Projet/img/bombe.png");
            who = QString("bombe");
        }
        Bonus* bonu = new Bonus(chemin, who);
        this->addItem(bonu);
        int x;
        if(bonu->getSpeedX()<0){
            x = QRandomGenerator::global()->bounded(200,600);
        }else if(bonu->getSpeedX()>0){
            x = QRandomGenerator::global()->bounded(0,400);
        }else{
            x = QRandomGenerator::global()->bounded(25,575);
        }
        bonu->setPos(x,200);
        this->bonus.push_back(bonu);
    }
}
void GameScene::createBoss(){
    if(score->getScore()>(speedGame-1)*50000 and bosses.isEmpty()){
        Boss* bo = new Boss(":Projet/img/boss.png",50+(speedGame-2)*10,this);
        this->addItem(bo);
        bo->setPos(225,0);
        this->bosses.push_back(bo);
        speedGame++;
        if(speedGame%2==0){
            this->ship->upSpeed();
        }
    }
}

// Bouge tt les items si de 400px pour faire une boucle
void GameScene::moveAll() {
    this->ship->moveAllShoot(400);
    this->ship->setY(ship->y()+400);
    this->life->setY(life->y()+400);
    this->score->setY(score->y()+400);
    this->nbombe_img->setY(nbombe_img->y()+400);
    this->nbombe->setY(nbombe->y()+400);
    for (auto enemie : enemies) {
        enemie->move(0,400);
        enemie->moveAllShoot(400);
    }
    for (auto asteroid : asteroids) {
        asteroid->move(0,400);
    }
    for (auto bonu : bonus) {
        bonu->move(0,400);
    }
    for (auto bo : bosses) {
        bo->setY(bo->y()+400);
        bo->moveAllShoot(400);
    }
}

//Déplace tt les items
void GameScene::moveAllEnemies(){
    for (auto enemie : enemies) {
        enemie->move(enemie->getSpeedX(),enemie->getSpeedY());
        enemie->setInterval(enemie->getInterval()+1);
        if(enemie->getInterval()>80 and enemie->pos().y()>400 and enemie->getLife()>0){
            enemie->shoot();
            enemie->setInterval(0);
        }
        enemie->moveAllShoot(speedGame*4);
    }
}
void GameScene::moveAllAsteroids() {
    for (auto asteroid : asteroids) {
        asteroid->move(asteroid->getSpeedX(),asteroid->getSpeedY());
    }
}
void GameScene::moveAllBonus() {
    for (auto bonu : bonus) {
        bonu->move(bonu->getSpeedX(),bonu->getSpeedY());
    }
}
void GameScene::moveAllBoss(){
    int sizeY = this->views()[0]->viewport()->size().height();
    for (auto bo : bosses) {
        if(bo->y()>=centerPoint.y()-sizeY/2+50 and bo->getSpeedY()!=0){
            if(bo->x()<50 or bo->x()>450){
                bo->setSpeedX(-bo->getSpeedX());
            }
            bo->setPos(bo->x()+bo->getSpeedX(),bo->y()-speedGame);
            bo->setInterval(bo->getInterval()+1);
            if(bo->getInterval()>50  and bo->getLife()>0){
                bo->shoot();
                bo->setInterval(0);
            }
        }else{
            bo->setY(bo->y()+bo->getSpeedY());
        }
        bo->moveAllShoot(speedGame*4);
    }
}

// Gestion de la collision
void GameScene::collision(){
    QList<Shoot*> listeDeleteShoot;
    for (auto shoot : *ship->getAllShoot()){
        for (auto enemie : enemies){
            if(enemie->collidesWithItem(shoot) and enemie->getLife()>=1){
                enemie->getHit(shoot->getDamageShoot());
                this->score->addScore(500);
                if(!listeDeleteShoot.contains(shoot)){
                    listeDeleteShoot.push_back(shoot);
                }
            }
        }
        for (auto asteroid : asteroids){
            if(asteroid->collidesWithItem(shoot) and asteroid->getLife()>=1){
                asteroid->getHit(shoot->getDamageShoot());
                this->score->addScore(100);
                if(!listeDeleteShoot.contains(shoot)){
                    listeDeleteShoot.push_back(shoot);
                }
            }
        }
        for (auto bo : bosses){
            if(bo->collidesWithItem(shoot) and bo->getLife()>=1){
                bo->getHit(shoot->getDamageShoot());
                this->score->addScore(50);
                if(!listeDeleteShoot.contains(shoot)){
                    listeDeleteShoot.push_back(shoot);
                }
            }
        }
    }
    for (auto shoot : listeDeleteShoot){
        ship->getAllShoot()->removeOne(shoot);
        delete shoot;
    }
    listeDeleteShoot.clear();
    for (auto enemie : enemies){
        if(enemie->collidesWithItem(ship) and enemie->getLife()>=1){
            this->life->setHit(2);
            enemie->getHit(5);
        }
        for(auto enemieShoot : *enemie->getAllShoot()){
            if(ship->collidesWithItem(enemieShoot)){
                this->life->setHit(1);
                if(!listeDeleteShoot.contains(enemieShoot)){
                    listeDeleteShoot.push_back(enemieShoot);
                }
            }
        }
        for (auto shoot : listeDeleteShoot){
            enemie->getAllShoot()->removeOne(shoot);
            delete shoot;
        }
        listeDeleteShoot.clear();
    }
    for (auto bo : bosses){
        if(bo->collidesWithItem(ship) and bo->getLife()>=1){
            this->life->setHit(6);
        }
        for(auto bossShoot : *bo->getAllShoot()){
            if(ship->collidesWithItem(bossShoot)){
                this->life->setHit(1);
                if(!listeDeleteShoot.contains(bossShoot)){
                    listeDeleteShoot.push_back(bossShoot);
                }
            }
        }
        for (auto shoot : listeDeleteShoot){
            bo->getAllShoot()->removeOne(shoot);
            delete shoot;
        }
        listeDeleteShoot.clear();
    }
    for (auto asteroid : asteroids){
        if(asteroid->collidesWithItem(ship) and asteroid->getLife()>=1){
            this->life->setHit(2);
            asteroid->getHit(5);
        }
    }
    QList<Bonus*> listeDeleteBonus;
    for (auto bonu : bonus){
        if(bonu->collidesWithItem(ship)){
            if(!listeDeleteBonus.contains(bonu)){
                listeDeleteBonus.push_back(bonu);
            }
            if(bonu->getWho()=="heal"){
                this->life->setHit(-2);
            }else{
                this->nbBombe++;
            }
        }
    }
    for (auto bonu : listeDeleteBonus){
        bonus.removeOne(bonu);
        delete bonu;
    }
}

// Supprime les items si ils sont en dehors de l'écran
void GameScene::deleteAll(){
    int sizeY = this->views()[0]->viewport()->size().height();
    for (auto oneshoot : *ship->getAllShoot()) {
        if(oneshoot->pos().y()<centerPoint.y()-sizeY/2+10){
            ship->getAllShoot()->removeOne(oneshoot);
            delete oneshoot;
        }
    }
    for (auto enemie : enemies) {
        for (auto oneshoot : *enemie->getAllShoot()) {
            if(oneshoot->y()>centerPoint.y()+sizeY/2+10 or enemie->pos().x()<5 or enemie->pos().x()>605){
                enemie->getAllShoot()->removeOne(oneshoot);
                delete oneshoot;
            }
        }
        if(enemie->pos().x()<-100 or enemie->pos().x()>700 or enemie->pos().y()>2000){
            enemies.removeOne(enemie);
            delete enemie;
        }
    }
    for (auto asteroid : asteroids) {
        if(asteroid->pos().x()<-100 or asteroid->pos().x()>700 or asteroid->pos().y()>2000){
            asteroids.removeOne(asteroid);
            delete asteroid;
        }
    }
    for (auto bonu : bonus) {
        if(bonu->pos().x()<-100 or bonu->pos().x()>700 or bonu->pos().y()>2000){
            bonus.removeOne(bonu);
            delete bonu;
        }
    }
    for (auto bo : bosses) {
        for (auto oneshoot : *bo->getAllShoot()) {
            if(oneshoot->y()>centerPoint.y()+sizeY/2+10){
                bo->getAllShoot()->removeOne(oneshoot);
                delete oneshoot;
            }
        }
        if(bo->pos().x()<-100 or bo->pos().x()>700 or bo->pos().y()>2000){
            bosses.removeOne(bo);
            delete bo;
        }
    }
}

// Reset la scene du jeu si on reviens dessus
void GameScene::reset(){
    this->slider->setValue(static_cast<int>(this->musique->getVolume()));
    this->centerPoint =  QPointF(300,800);
    for (auto enemie : enemies){
        enemies.removeOne(enemie);
        delete enemie;
    }
    for (auto asteroid : asteroids){
        asteroids.removeOne(asteroid);
        delete asteroid;
    }
    for (auto bonu : bonus){
        bonus.removeOne(bonu);
        delete bonu;
    }
    for (auto bo : bosses){
        bosses.removeOne(bo);
        delete bo;
    }
    this->ship->reset();
    this->keyPressed.clear();
    ship->getAllShoot()->clear();
    this->ship->setPos(250,900);
    this->life->reset();
    this->life->setPos(centerPoint.x() + 200, centerPoint.y() + 280);
    this->score->reset();
    this->score->setPos(centerPoint.x() - 300, centerPoint.y() - 300);
    this->nbombe_img->setPos(centerPoint.x() - 295, centerPoint.y() + 295);
    this->nbombe->setPos(centerPoint.x() - 280, centerPoint.y() + 295);
    this->nbBombe = 0;
    this->speedGame = 2;
}


// Partie SpaceShip.cpp
void SpaceShip::moveUp() {
    QPointF pos = this->pos();

    int newY = pos.y() - speed;
    int sizeY = parent->views()[0]->viewport()->size().height();
    if (newY < parent->getCenterPoint()->y()-sizeY/2) {
        newY = parent->getCenterPoint()->y()-sizeY/2;
    }
    this->setPos(pos.x(), newY);
}
void SpaceShip::moveDown() {
    QPointF pos = this->pos();

    int newY = pos.y() + speed;
    int sizeY = parent->views()[0]->viewport()->size().height();
    if (newY > parent->getCenterPoint()->y()+sizeY/2-80) {
        newY = parent->getCenterPoint()->y()+sizeY/2-80;
    }
    this->setPos(pos.x(), newY);
}
void SpaceShip::shoot(){
    Shoot* shoot1 = new Shoot(":Projet/img/missile.png", 1);
    parent->addItem(shoot1);
    shoot1->setPos(this->pos().x()+19,this->pos().y()+15);
    this->shoots.push_back(shoot1);

    Shoot* shoot2 = new Shoot(":Projet/img/missile.png", 1);
    parent->addItem(shoot2);
    shoot2->setPos(this->pos().x()+77,this->pos().y()+15);
    this->shoots.push_back(shoot2);
}

// Partie Enemies.cpp
void Enemies::shoot(){
    Shoot* shoot = new Shoot(":Projet/img/missile2.png", 1);
    parent->addItem(shoot);
    shoot->setPos(this->pos().x()+25,this->pos().y()+30);
    this->shoots.push_back(shoot);
}

// Partie Boss.cpp
void Boss::shoot(){
    Shoot* shoot1 = new Shoot(":Projet/img/missile2.png", 1,-2);
    parent->addItem(shoot1);
    shoot1->setPos(this->pos().x()+52,this->pos().y()+50);
    this->shoots.push_back(shoot1);

    Shoot* shoot2 = new Shoot(":Projet/img/missile2.png", 1,-1);
    parent->addItem(shoot2);
    shoot2->setPos(this->pos().x()+65,this->pos().y()+50);
    this->shoots.push_back(shoot2);

    Shoot* shoot3 = new Shoot(":Projet/img/missile2.png", 1,1);
    parent->addItem(shoot3);
    shoot3->setPos(this->pos().x()+80,this->pos().y()+50);
    this->shoots.push_back(shoot3);

    Shoot* shoot4 = new Shoot(":Projet/img/missile2.png", 1,2);
    parent->addItem(shoot4);
    shoot4->setPos(this->pos().x()+95,this->pos().y()+50);
    this->shoots.push_back(shoot4);
}