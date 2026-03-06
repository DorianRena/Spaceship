#include "MainWindow.h"

// MainWindow
MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);
    this->menu = new Menu(this);

    this->mainView = new QGraphicsView;
    this->mainView->setScene(menu);

    this->setCentralWidget(mainView);
    this->setWindowTitle("SPACESHIP");
    this->setFixedSize(625, 625);

}

QGraphicsView *MainWindow::getView(){
    return mainView;
}

