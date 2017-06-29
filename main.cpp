#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    //Create application and show main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
