#ifndef BOOKLOADER_H
#define BOOKLOADER_H

#include <QString>
#include <Vector>
#include <book.h>

class BookLoader
{
public:

    BookLoader();

    //Get Book methods
    Book* getBook(int index);
    Book* getBook(QString SeriesName, int BookNumber);
    Book* getBook(QString Title);

    //Delete Book Methods
    void deleteBook(int index);
    void deleteBook(QString Title);

    //Add Book
    void addBook(QString Path, QString Series, int BookNumber);
    void addBook(Book book);

    //Return vector of all books
    vector<Book> getAllBooks();

    //Get, and set scale
    double getScaleFactor();
    void setScaleFactor(double newScale);

    //Get and set current book
    void setCurrentBook(Book*newBook);
    Book* getCurrentBook();

    //Get number of books
    int getSize();

    //Save and load data
    void loadBooks();
    void saveBooks();

    //Performs bubble sort on books vector
    void sortBooks();


private:

    //main data structure, holds book
    vector<Book> books;

    //scale factor for page zooming
    double scaleFactor = 1;

    //represents the current book
    Book*currentBook;

};


#endif // BOOKLOADER_H
