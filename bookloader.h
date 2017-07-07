#ifndef BOOKLOADER_H
#define BOOKLOADER_H

#include <QString>
#include <Vector>
#include <book.h>

class BookLoader
{
public:
    Book getBook(int index);
    Book getBook(QString SeriesName, int BookNumber);
    void deleteBook(QString series, int number);
    void addBook(QString Path, QString Series, int BookNumber);
    vector<Book> getAllBooks();
    double getScaleFactor();
    void setScaleFactor(double newScale);
    void setCurrentBook(Book newBook);
    Book getCurrentBook();
    void loadBooks();
    void saveBooks();


private:

    //main data structure, holds book
    vector<Book> books;

    //scale factor for page zooming
    double scaleFactor = 1;

    //represents the current book
    Book currentBook;

};


#endif // BOOKLOADER_H
