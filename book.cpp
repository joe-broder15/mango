#include "book.h"
#include <QDir>
#include <QPixmap>

//Constructor
Book::Book(int BookNumber, QString p, QString Series)
{
    //Set properties
    bookNumber = BookNumber;
    series = Series;
    bookMark = 0;

    //Create a directory object for the given path
    path = p;
    QDir dir(path);
    //For each item in the directory, create a Pixmap (image) and push back on the vector
    foreach (QFileInfo var, dir.entryInfoList()) {
         if(!var.isDir()){
             pages.push_back(var.absoluteFilePath());
         }
    }

}

//Returns image for page
QPixmap Book::getPage(int pageNumber)
{
    QPixmap page(pages.at(pageNumber));
    return page;
}

//Get series
QString Book::getSeries()
{
    return series;
}

//Set series
void Book::setSeries(QString Series)
{
    series = Series;
}

//Get book Bumber
int Book::getBookNumber()
{
    return bookNumber;
}

//set book number
void Book::setBookNumber(int BookNumber)
{
    bookNumber = BookNumber;
}

//get current page
int Book::getCurrentPage()
{
    return currentPage;
}

//set current page
void Book::setCurrentPage(int CurrentPage)
{
    currentPage = CurrentPage;
}

//get bookmark
int Book::getBookMark()
{
    return bookMark;
}

//set bookmark
void Book::setBookMark(int BookMark)
{
    bookMark = BookMark;
}

//get path
QString Book::getPath()
{
    return path;
}

//set path
void Book::setPath(QString Path)
{
    path = Path;
}

//Get size
int Book::getSize()
{
    return pages.size();
}
