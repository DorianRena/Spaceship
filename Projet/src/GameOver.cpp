#include "GameOver.h"


GameOver::GameOver(QObject* parent){
    this->setParent(parent);

    this->background.load(":/Projet/img/GameOver.png");
    this->setSceneRect(0, 0, background.width(), background.height());
    this->addPixmap(background);

    this->boutton_valider_nom = new QPushButton("valider  votre  nom");
    this->boutton_valider_nom->setStyleSheet(
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
    QGraphicsProxyWidget* widget_valider_nom = this->addWidget(boutton_valider_nom);
    widget_valider_nom->setPos(167, 515);
    widget_valider_nom->setMinimumSize(150,30);

    connect(this->boutton_valider_nom,SIGNAL(clicked(bool)),this,SLOT(saveName()));
    connect(this->boutton_valider_nom,SIGNAL(clicked(bool)),this->parent(),SLOT(menuGameRetry()));
}

void GameOver::createScoreboard(QString fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Impossible d'ouvrir le fichier" << fileName;
        return;
    }
    QTextStream index_line(&file);
    QList<QList<QString>> data;
    while (!index_line.atEnd())
    {
        QString line = index_line.readLine();
        data.append(line.split(';'));
    }
    file.close();

    valueSort.clear();
    for(int i = 1; i < data.size(); i++){
        int value = data[i][0].toInt();
        valueSort.append(qMakePair(value, data[i][1]));
    }
    valueSort.append(tempoValue);
    std::sort(valueSort.begin(), valueSort.end());
    int newP = 0;
    int iter = 1;
    const int numRows = 15;
    const int numCols = 3;
    const int cellSizeW = 193;
    const int cellSizeH = 30;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if(row <6 || row>12) {
                QGraphicsRectItem *scoreboard = new QGraphicsRectItem((col * cellSizeW)+10, (row * cellSizeH)+10,
                                                                      cellSizeW,cellSizeH);
                scoreboard->setPen(QPen(Qt::white));
                scoreboard->setBrush(QBrush(QColor(255, 255, 255, 0)));
                if (col == 0 && row == 0) {
                    QGraphicsTextItem *text_cell1 = new QGraphicsTextItem("Numéro au classement");
                    text_cell1->setDefaultTextColor(Qt::red);
                    QFont font;
                    font.setBold(true);
                    text_cell1->setFont(font);

                    text_cell1->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell1->boundingRect().width() / 2,
                                       row * cellSizeH+10 + cellSizeH / 2 - text_cell1->boundingRect().height() / 2);
                    this->addItem(text_cell1);
                    this->allItem.push_back(text_cell1);
                } else if (col == 1 && row == 0) {
                    QGraphicsTextItem *text_cell2 = new QGraphicsTextItem("Nom du joueur");
                    text_cell2->setDefaultTextColor(Qt::red);
                    QFont font;
                    font.setBold(true);
                    text_cell2->setFont(font);

                    text_cell2->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell2->boundingRect().width() / 2,
                                       row * cellSizeH+10 + cellSizeH / 2 - text_cell2->boundingRect().height() / 2);
                    this->addItem(text_cell2);
                    this->allItem.push_back(text_cell2);
                }
                else if (col == 2 && row == 0) {
                    QGraphicsTextItem *text_cell3 = new QGraphicsTextItem("Score");
                    text_cell3->setDefaultTextColor(Qt::red);
                    QFont font;
                    font.setBold(true);
                    text_cell3->setFont(font);

                    text_cell3->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell3->boundingRect().width() / 2,
                                       row * cellSizeH+10 + cellSizeH / 2 - text_cell3->boundingRect().height() / 2);
                    this->addItem(text_cell3);
                    this->allItem.push_back(text_cell3);
                }
                else if (col == 0 && row == 13) {
                    QGraphicsTextItem *text_cell_player1 = new QGraphicsTextItem("Votre numéro au classement");
                    text_cell_player1->setDefaultTextColor(Qt::red);
                    QFont font;
                    font.setBold(true);
                    text_cell_player1->setFont(font);

                    text_cell_player1->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell_player1->boundingRect().width() / 2,
                                              row * cellSizeH+10 + cellSizeH / 2 - text_cell_player1->boundingRect().height() / 2);
                    this->addItem(text_cell_player1);
                    this->allItem.push_back(text_cell_player1);
                } else if (col == 1 && row == 13) {
                    QGraphicsTextItem *text_cell_player2 = new QGraphicsTextItem("Votre nom de joueur");
                    text_cell_player2->setDefaultTextColor(Qt::red);
                    QFont font;
                    font.setBold(true);
                    text_cell_player2->setFont(font);

                    text_cell_player2->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell_player2->boundingRect().width() / 2,
                                              row * cellSizeH+10 + cellSizeH / 2 - text_cell_player2->boundingRect().height() / 2);
                    this->addItem(text_cell_player2);
                    this->allItem.push_back(text_cell_player2);
                }
                else if (col == 2 && row == 13) {
                    QGraphicsTextItem *text_cell_player3 = new QGraphicsTextItem("Votre score");
                    text_cell_player3->setDefaultTextColor(Qt::red);
                    QFont font;
                    font.setBold(true);
                    text_cell_player3->setFont(font);

                    text_cell_player3->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell_player3->boundingRect().width() / 2,
                                              row * cellSizeH+10 + cellSizeH / 2 - text_cell_player3->boundingRect().height() / 2);
                    this->addItem(text_cell_player3);
                    this->allItem.push_back(text_cell_player3);
                }
                else if(row >0 && row <6 && (iter-newP<=valueSort.size() || playerPos() == iter)){
                    if(playerPos() == iter){
                        if(col == 0){
                            QGraphicsTextItem *text_cell1 = new QGraphicsTextItem(QString::number(iter));
                            text_cell1->setDefaultTextColor(Qt::yellow);

                            text_cell1->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell1->boundingRect().width() / 2,
                                               row * cellSizeH+10 + cellSizeH / 2 - text_cell1->boundingRect().height() / 2);
                            this->addItem(text_cell1);
                            this->allItem.push_back(text_cell1);
                        }else if(col == 1){
                            QGraphicsTextItem *text_cell2 = new QGraphicsTextItem("VOUS");
                            text_cell2->setDefaultTextColor(QColor::fromRgb(185, 0,255));
                            QFont font;
                            font.setBold(true);
                            text_cell2->setFont(font);

                            text_cell2->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell2->boundingRect().width() / 2,
                                               row * cellSizeH+10 + cellSizeH / 2 - text_cell2->boundingRect().height() / 2);
                            this->addItem(text_cell2);
                            this->allItem.push_back(text_cell2);
                        }else if(col == 2){
                            QGraphicsTextItem *text_cell3 = new QGraphicsTextItem(QString::number(score));
                            text_cell3->setDefaultTextColor(Qt::yellow);

                            text_cell3->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell3->boundingRect().width() / 2,
                                               row * cellSizeH+10 + cellSizeH / 2 - text_cell3->boundingRect().height() / 2);
                            this->addItem(text_cell3);
                            this->allItem.push_back(text_cell3);
                            iter++;
                            newP++;
                        }
                    }else{
                        if(col == 0){
                            QGraphicsTextItem *text_cell1 = new QGraphicsTextItem(QString::number(iter));
                            text_cell1->setDefaultTextColor(Qt::yellow);

                            text_cell1->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell1->boundingRect().width() / 2,
                                               row * cellSizeH+10 + cellSizeH / 2 - text_cell1->boundingRect().height() / 2);
                            this->addItem(text_cell1);
                            this->allItem.push_back(text_cell1);
                        }else if(col == 1){
                            QGraphicsTextItem *text_cell2 = new QGraphicsTextItem(valueSort[valueSort.size()-iter+newP].second);
                            text_cell2->setDefaultTextColor(Qt::yellow);

                            text_cell2->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell2->boundingRect().width() / 2,
                                               row * cellSizeH+10 + cellSizeH / 2 - text_cell2->boundingRect().height() / 2);
                            this->addItem(text_cell2);
                            this->allItem.push_back(text_cell2);
                        }else if(col == 2){
                            QGraphicsTextItem *text_cell3 = new QGraphicsTextItem(QString::number(valueSort[valueSort.size()-iter+newP].first));
                            text_cell3->setDefaultTextColor(Qt::yellow);

                            text_cell3->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell3->boundingRect().width() / 2,
                                               row * cellSizeH+10 + cellSizeH / 2 - text_cell3->boundingRect().height() / 2);
                            this->addItem(text_cell3);
                            this->allItem.push_back(text_cell3);
                            iter++;
                        }
                    }

                }else if(row == 14){
                    if(col == 0){

                        QGraphicsTextItem *text_cell_player1 = new QGraphicsTextItem(QString::number(playerPos()));
                        text_cell_player1->setDefaultTextColor(Qt::yellow);

                        text_cell_player1->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell_player1->boundingRect().width() / 2,
                                                  row * cellSizeH+10 + cellSizeH / 2 - text_cell_player1->boundingRect().height() / 2);
                        this->addItem(text_cell_player1);
                        this->allItem.push_back(text_cell_player1);
                    }else if(col == 1){
                        playerName = new QLineEdit();
                        playerName->setAlignment(Qt::AlignCenter);
                        QPalette style = playerName->palette();
                        style.setBrush(QPalette::Base, Qt::black);
                        style.setColor(QPalette::Text, Qt::yellow);
                        playerName->setPalette(style);
                        playerName->setGeometry(col * cellSizeW+10, row * cellSizeH+10, cellSizeW, cellSizeH);
                        QGraphicsProxyWidget* text_PlayerName = this->addWidget(playerName);
                        this->allItem.push_back(text_PlayerName);
                    }else if(col == 2){
                        QGraphicsTextItem *text_cell_player3 = new QGraphicsTextItem(QString::number(score));
                        text_cell_player3->setDefaultTextColor(Qt::yellow);

                        text_cell_player3->setPos(col * cellSizeW+10 + cellSizeW / 2 - text_cell_player3->boundingRect().width() / 2,
                                                  row * cellSizeH+10 + cellSizeH / 2 - text_cell_player3->boundingRect().height() / 2);
                        this->addItem(text_cell_player3);
                        this->allItem.push_back(text_cell_player3);
                        iter++;
                    }
                }
                this->addItem(scoreboard);
                this->allItem.push_back(scoreboard);
            }
        }
    }

}

void GameOver::addPlayer(QString fileName, QString newName) {
    QString realPath = "Score.csv"; 

    QFile file(realPath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier en écriture :" << realPath;
        return;
    }

    QTextStream out(&file);
    out << score << ";" << newName << "\n";
    file.close();
}

void GameOver::setScore(int score) {
    this->score = score;
    reset();
    QFile localFile("Score.csv");
    if (localFile.exists()) {
        createScoreboard("Score.csv");
    } else {
        createScoreboard(":/Projet/other/Score.csv");
    }
}

int GameOver::playerPos(){
    int pos =1;
    for (int i = valueSort.size()-1;i>=0;i--){
        if(valueSort[i].first >score){
            pos++;
        }
        else{
            return pos;
        }
    }
    return pos;
}

void GameOver::saveName(){
    QString newName = playerName->text();
    if(newName == ""){
        newName = "Unknow";
    }
    addPlayer(":/Projet/other/Score.csv", newName);
}

void GameOver::reset(){
    for (auto item : allItem){
        this->removeItem(item);
        delete item;
    }
    allItem.clear();
}

QPair<int, QString> GameOver::getBestPlayer(QString fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Impossible d'ouvrir le fichier" << fileName;
        return qMakePair(0, "Aucun joueur");
    }
    QTextStream index_line(&file);
    QList<QList<QString>> data;
    while (!index_line.atEnd())
    {
        QString line = index_line.readLine();
        data.append(line.split(';'));
    }
    file.close();

    valueSort.clear();
    for(int i = 1; i < data.size(); i++){
        int value = data[i][0].toInt();
        valueSort.append(qMakePair(value, data[i][1]));
    }
    valueSort.append(tempoValue);
    std::sort(valueSort.begin(), valueSort.end());
    if(valueSort.size()!=0){
        return valueSort[valueSort.size()-1];
    }
    else{
        return qMakePair(0, "Aucun joueur");
    }
}