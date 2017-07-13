#include "book.h"
#include <QDebug>
#include <QDir>
#include <QPixmap>

//Constructor
Book::Book(int BookNumber, QString p, QString Series)
{
    //Set properties
    bookNumber = BookNumber;
    series = Series;
    bookMark = 0;
    currentPage = 0;

    title = series + " " + QString::number(bookNumber);

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

//Blank Constructor
Book::Book()
{
    series = "";
    bookNumber = 0;
    currentPage = 0;
    bookMark = 0;
    path = "";
    title = "";
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

//Get title
QString Book::getTitle()
{
    return title;
}

//Set title
void Book::setTitle(QString newTitle)
{
    title = newTitle;
}

//check if empty
bool Book::empty()
{
    if(path.trimmed().isEmpty() && series.trimmed().isEmpty() && bookNumber==0){
        return true;
    } else {
        return false;
    }

}
