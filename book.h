#ifndef MANGA_H
#define MANGA_H
#include <QString>
#include <vector>
#include <QPixmap>

class Book
{
public:
    Book(int BookNumber, QString Path, QString Series);
    QPixmap getPage(int pageNumber);
    QString getSeries();
    void setSeries(QString Series);
    int getBookNumber();
    void setBookNumber(int BookNumber);
    int getCurrentPage();
    void setCurrentPage(int CurrentPage);
    int getBookMark();
    void setBookMark(int BookMark);
    QString getPath();
    void setPath(QString Path);
    int getSize();

private:
    std::vector<QString> pages;
    QString series;
    int bookNumber;
    int currentPage;
    int bookMark;
    QString path;

};

#endif // MANGA_H
