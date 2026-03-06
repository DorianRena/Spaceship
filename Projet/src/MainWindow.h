#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include "Menu.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
private :
    Menu* menu;
    QGraphicsView* mainView;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow(){
        delete menu;
    };
    QGraphicsView* getView();

};

#endif //QT_MAINWINDOW_H