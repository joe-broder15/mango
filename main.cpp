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





    BookLoader bl;
    Book book1;
    Book book2;
    Book book3;
    Book book4;
    Book book5;
    Book book6;

    bl.addBook(book1);
    bl.addBook(book2);
    bl.addBook(book3);
    bl.addBook(book4);
    bl.addBook(book5);
    bl.addBook(book6);

    bl.saveBooks();
    bl.loadBooks();

    //qDebug()<<QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    return a.exec();

}
