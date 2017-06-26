#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imageloader.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    ImageLoader imageloader;
};

#endif // MAINWINDOW_H
