#ifndef MANGA_H
#define MANGA_H
#include <QString>
#include <vector>
#include <QPixmap>
using namespace std;

class Book
{
public:
    //Constructor
    Book();
    Book(int BookNumber, QString Path, QString Series);

    //Returns image for page
    QPixmap getPage(int pageNumber);

    //Get and set series
    QString getSeries();
    void setSeries(QString Series);

    //Get and set number
    int getBookNumber();
    void setBookNumber(int BookNumber);

    //Get and set current page
    int getCurrentPage();
    void setCurrentPage(int CurrentPage);

    //Get and set Bookmark
    int getBookMark();
    void setBookMark(int BookMark);

    //Get and set path
    QString getPath();
    void setPath(QString Path);

    //Get num ofpages
    int getSize();

    //Get title
    QString getTitle();

    //Set title
    void setTitle(QString newTitle);

    //Check if empty
    bool empty();

    //Get Page For Path
    QString getPathForIndex(int Page);

private:
    vector<QString> pages;
    QString series;
    int bookNumber;
    int currentPage;
    int bookMark;
    QString title;
    QString path;

};

#endif // MANGA_H
