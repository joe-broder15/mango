#include "mainwindow.h"
#include "book.h"
#include "bookloader.h"
#include <QApplication>
#include <QDebug>
#include <QStandardPaths>


int main(int argc, char *argv[])
{
    //Create application and show main window
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("mango");
    MainWindow w;
    w.show();
    return a.exec();

}
