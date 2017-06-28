#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imageloader.h"
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
    void on_getMangaButton_clicked();

    void on_nextPageButton_clicked();

    void on_previousPageButton_clicked();

    void on_pageJumpButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void on_zoomResetButton_clicked();

    void setImageForPage();

private:
    Ui::MainWindow *ui;
    ImageLoader imageloader;
    QGraphicsScene * scene = new QGraphicsScene(this);
};

#endif // MAINWINDOW_H
