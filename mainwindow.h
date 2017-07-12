#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imageloader.h"
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
    //Methods for ui events
    void on_getMangaButton_clicked();

    void on_nextPageButton_clicked();

    void on_previousPageButton_clicked();

    void on_pageJumpButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void on_zoomResetButton_clicked();

    void on_firstPageButton_clicked();

    void on_lastPageButton_clicked();


private:
    Ui::MainWindow *ui;

    //imageloader object
    ImageLoader imageloader;
    BookLoader bookLoader;

    //scene for graphics widget
    QGraphicsScene * scene = new QGraphicsScene(this);
};

#endif // MAINWINDOW_H
