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
    //Methods for ui events
    void on_addMangaButton_clicked();

    //Reload List
    void reloadMangaList();

    void on_deleteMangaButton_clicked();

    void on_selectMangaButton_clicked();

private:
    Ui::MainWindow *ui;

    //imageloader object
    BookLoader bookLoader;

    //scene for graphics widget
    QGraphicsScene * scene = new QGraphicsScene;

};

#endif // MAINWINDOW_H
