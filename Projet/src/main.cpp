#include <QApplication>
#include <QResource>
#include "MainWindow.h"


int main(int argc, char *argv[]) {

    QApplication application(argc, argv);

    Q_INIT_RESOURCE(ressource);

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
