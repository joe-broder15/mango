#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QString>
#include <vector>
#include <QDir>
using namespace std;

class ImageLoader
{
public:
    void loadBook(QString path);

    QString getPage(int pageNumber);

    int getCurrentPage();

    int getLength();

    void setCurrentPage(int page);

private:
    int currentPage;
    vector<QString> pages;


};


#endif // IMAGELOADER_H
