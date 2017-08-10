#include "mainwindow.h"
#include "book.h"
#include "bookloader.h"
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>
#include <QStandardPaths>


int main(int argc, char *argv[])
{
    //Create application and show main window
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("mango");
    MainWindow w;
    w.show();
    return a.exec();

}
