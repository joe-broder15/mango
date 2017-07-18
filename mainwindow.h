#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "book.h"
#include "bookloader.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QListWidgetItem>


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

    //ASYNC Load thumbnails to gallery
    void loadThumbNails();

    //Methods for ui events
    void on_addMangaButton_clicked();

    void on_deleteMangaButton_clicked();

    void on_nextPageButton_clicked();

    void on_previousPageButton_clicked();

    void on_firstPageButton_clicked();

    void on_lastPageButton_clicked();

    void on_pageJumpButton_clicked();

    void on_zoomResetButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void on_thumbnailListWidget_itemClicked(QListWidgetItem *item);

    void on_mangaListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_thumbnailSplitter_splitterMoved(int pos, int index);

private:
    Ui::MainWindow *ui;

    //imageloader object
    BookLoader bookLoader;

    //scene for graphics widget
    QGraphicsScene * scene = new QGraphicsScene;

    bool isGalleryView = false;

};

#endif // MAINWINDOW_H
