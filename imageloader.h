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
    //Method to get pages for a given book(directory)
    void loadBook(QString path);

    //Returns an image for a page number
    QPixmap getPage(int pageNumber);

    //Gets the current page number
    int getCurrentPage();

    //Returns length of "pages" vector
    int getLength();

    //sets current page
    void setCurrentPage(int page);

    //Increase Factor for zooming
    void increaseScaleFactor();

    //Decrease factor for zooming
    void decreaseScaleFactor();

    //Set custom factor for zooming (used in reset)
    void setScaleFactor(double newFactor);

private:
    //Represents current page
    int currentPage;

    //Stores pages as QPixmap items (images)
    vector<QPixmap> pages;

    //Factor for zoom
    double scaleFactor = 1;


};


#endif // IMAGELOADER_H
