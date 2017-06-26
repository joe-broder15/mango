#include <QDir>
#include <QString>
#include "imageloader.h"


void ImageLoader::loadBook(QString path){
    pages.clear();

    QDir dir(path);

    foreach (QFileInfo var, dir.entryInfoList()) {
         if(!var.isDir()){
             pages.push_back(var.absoluteFilePath());
         }
    }
}

QString ImageLoader::getPage(int pageNumber){
    return pages.at(pageNumber);
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

