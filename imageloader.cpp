#include <QDir>
#include <QString>
#include "imageloader.h"


void ImageLoader::loadBook(QString path){
    pages.clear();

    QDir dir(path);

    foreach (QFileInfo var, dir.entryInfoList()) {
         if(!var.isDir()){
             pages.push_back(QPixmap(var.absoluteFilePath()));
         }
    }
}

QPixmap ImageLoader::getPage(int pageNumber){
    QPixmap p = pages.at(pageNumber);
    p = p.scaled(scaleFactor * p.size());
    return p;
}

int ImageLoader::getCurrentPage(){
    return currentPage;
}

void ImageLoader::setCurrentPage(int page){
    currentPage = page;
}

int ImageLoader::getLength(){
    return pages.size();
}

void ImageLoader::increaseScaleFactor(){
    scaleFactor += .1;
}

void ImageLoader::decreaseScaleFactor(){
    scaleFactor -= .1;

}

void ImageLoader::setScaleFactor(double newScaleFactor){
    scaleFactor = newScaleFactor;
}

