#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QString>
#include <vector>
#include <QDir>
#include <QPixmap>
using namespace std;

class ImageLoader
{
public:
    void loadBook(QString path);

    QPixmap getPage(int pageNumber);

    int getCurrentPage();

    int getLength();

    void setCurrentPage(int page);

    void increaseScaleFactor();

    void decreaseScaleFactor();

    void setScaleFactor(double newFactor);

private:
    int currentPage;
    vector<QPixmap> pages;
    double scaleFactor = 1;


};


#endif // IMAGELOADER_H
