#include "bookloader.h"
#include "book.h"
#include <QString>
#include <fstream>
#include <vector>
#include <string>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
using namespace std;

//Get book for index
Book* BookLoader::getBook(int index){

    //Create and return a pointer to the indexed book
    Book * book = &books[index];
    return book;
}

//Get book for info (search) BOOK MUST EXIST WITHIN BOOKS VECTOR
Book* BookLoader::getBook(QString SeriesName, int BookNumber){

    //get size
    int size = books.size();

    for(int i=0; i <= size; i++)
    {
        //Search for item, then create and return a pointer for it
        if(books[i].getSeries() == SeriesName && books[i].getBookNumber() == BookNumber){
            Book * book = &books[i];
            return book;
        }
    }
}

//Get book for title (search) BOOK MUST EXIST WITHIN BOOKS VECTOR
Book* BookLoader::getBook(QString Title){

    //get size
    int size = books.size();

    for(int i=0; i <= size; i++)
    {
        //Search for item, then create and return a pointer for it
        if(books[i].getTitle() == Title){
            Book * book = &books[i];
            return book;
        }
    }
}

//Remove book for index
void BookLoader::deleteBook(int index){

    //Get siz3
    int size = books.size();

    //Copy items forward
    for(int i = index; i <= size; i++)
    {
        books[i] = books[i + 1];
    }

    //Remove extra last item
    books.pop_back();
}

//Remove book for info
void BookLoader::deleteBook(QString SeriesName, int BookNumber){

    //Get size
    int size = books.size();

    for(int i=0; i <= size; i++)
    {

        //Search for item
        if(books[i].getSeries() == SeriesName && books[i].getBookNumber() == BookNumber){

            //Copy it forward
            for(int i; i<=size; i++){
                 books[i] = books[i+1];
            }

            //Pop Back and remove last item
            books.pop_back();
            return;

         }
    }
}

//Add Book for info (make new book
void BookLoader::addBook(QString Path, QString Series, int BookNumber){
    Book b(BookNumber, Path, Series);
    books.push_back(b);
}

//Add book for book object
void BookLoader::addBook(Book book){
    books.push_back(book);
}

//Get all books
vector<Book> BookLoader::getAllBooks(){
    return books;
}

//Get  scale
double BookLoader::getScaleFactor(){
    return scaleFactor;
}

//Set Scale
void BookLoader::setScaleFactor(double scale){
    scaleFactor = scale;
}

//Get Current Book
Book* BookLoader::getCurrentBook(){
    return currentBook;
}

//Set current book
void BookLoader::setCurrentBook(Book newBook){
    currentBook = &newBook;
}

//Get number of books
int BookLoader::getSize(){
    return (int)(books.size());
}

//Save books
void BookLoader::saveBooks(){

    //Create and open file to save data
    QDir dir = QDir::root();
    dir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/mango");
    QString filename = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/mango/saveData.txt";
    QFile file(filename);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "ERROR";
    }

    QTextStream stream(&file);

    //Write data out for each book
    for(int i=0; i<(int)(books.size()); i++){
        stream<< "xxxxxx" << endl;
        stream<< books[i].getSeries() << endl;
        stream<< QString::number(books[i].getBookNumber()) << endl;
        stream<< books[i].getPath() << endl;
        stream<< QString::number(books[i].getBookMark()) << endl;
    }
    file.flush();
    file.close();


}

//Load Books
void BookLoader::loadBooks(){
    //Create and open file to save data
    QString filename = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/mango/saveData.txt";
    QFile file(filename);

    //check if file exists
    if(!file.exists()){
        return;
    }

    //Open File
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "ERROR";
    }

    //Stream Object
    QTextStream stream(&file);

    //Clear all books
    books.clear();

    //Read data
    //Create counter to track lines
    int count = 0;

    //Create temp book variables
    QString tempSeries;
    int tempBookNumber;
    QString tempPath;
    int tempBookMark;

    while (!stream.atEnd())
    {
        QString line = stream.readLine();

        if(line == "xxxxxx"){
          count = 0;

        } else if(count == 1){
            tempSeries = line;

        } else if(count == 2){
            tempBookNumber = line.toInt();

        } else if(count == 3){
            tempPath = line;

        } else if (count == 4){
            tempBookMark = line.toInt();
            Book newBook(tempBookNumber, tempPath, tempSeries);
            newBook.setBookMark(tempBookMark);
            books.push_back(newBook);
        }

        count++;

    }
    file.close();
}

