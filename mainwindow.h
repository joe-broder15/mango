#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "book.h"
#include "bookloader.h"
#include <QMainWindow>
#include <QGraphicsScene>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //Reload List
    void reloadMangaList();

    //Load image for current page
    void loadCurrentPage();

    //Methods for ui events
    void on_addMangaButton_clicked();

    void on_deleteMangaButton_clicked();

    void on_selectMangaButton_clicked();


    void on_nextPageButton_clicked();

    void on_previousPageButton_clicked();

    void on_firstPageButton_clicked();

    void on_lastPageButton_clicked();

    void on_pageJumpButton_clicked();

    void on_zoomResetButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

private:
    Ui::MainWindow *ui;

    //imageloader object
    BookLoader bookLoader;

    //scene for graphics widget
    QGraphicsScene * scene = new QGraphicsScene;

};

#endif // MAINWINDOW_H
