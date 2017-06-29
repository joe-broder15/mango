#include <QDir>
#include <QString>
#include "imageloader.h"

//Load book for file path
void ImageLoader::loadBook(QString path){
    //clear current book
    pages.clear();

    //Create a directory object for the given path
    QDir dir(path);

    //For each item in the directory, create a Pixmap (image) and push back on the vector
    foreach (QFileInfo var, dir.entryInfoList()) {
         if(!var.isDir()){
             pages.push_back(QPixmap(var.absoluteFilePath()));
         }
    }
}

//Get page for number
QPixmap ImageLoader::getPage(int pageNumber){
    QPixmap p = pages.at(pageNumber);

    //Resize image by zoom factor
    p = p.scaled(scaleFactor * p.size());
    return p;
}

//Accessor for currentPage
int ImageLoader::getCurrentPage(){
    return currentPage;
}

//Mutator for currentPage
void ImageLoader::setCurrentPage(int page){
    currentPage = page;
}

//Return book length
int ImageLoader::getLength(){
    return pages.size();
}

//Increase scale by 10%
void ImageLoader::increaseScaleFactor(){
    scaleFactor *= 1.1;
}

//Decrease scale by 10%
void ImageLoader::decreaseScaleFactor(){
    scaleFactor *= .9;

}

//Ser custom scale
void ImageLoader::setScaleFactor(double newScaleFactor){
    scaleFactor = newScaleFactor;
}

