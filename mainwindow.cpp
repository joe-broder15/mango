#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageloader.h"
#include <QPixmap>
#include <QMessageBox>
#include <qDebug>
// /Users/admin/Desktop/testManga

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_getMangaButton_clicked()
{
    imageloader.loadBook(ui->getMangaLineEdit->text());
    imageloader.setCurrentPage(0);
    ui->pageLabel->setText("1/" + QString::number(imageloader.getLength()));

    QPixmap pic(imageloader.getPage(0));
    ui->pageDisplay->setPixmap(pic.scaled(ui->pageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::on_nextPageButton_clicked()
{
    if(imageloader.getLength() == 0){
        QMessageBox::critical(this, "No manga", "Please select a manga!");
        return;
    } else if(imageloader.getCurrentPage() == imageloader.getLength() - 1){
        QMessageBox::information(this, "Finished", "You have finished this manga!");
    } else {
        int currentPage = imageloader.getCurrentPage() + 1;
        imageloader.setCurrentPage(currentPage);
        ui->pageLabel->setText(QString::number(currentPage + 1) + "/" + QString::number(imageloader.getLength()));
        QPixmap pic(imageloader.getPage(imageloader.getCurrentPage()));
        ui->pageDisplay->setPixmap(pic.scaled(ui->pageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }


}

void MainWindow::on_previousPageButton_clicked()
{
    if(imageloader.getLength() == 0){
        QMessageBox::critical(this, "No manga", "Please select a manga!");
        return;
    }else if(imageloader.getCurrentPage() == 0){
        QMessageBox::critical(this, "First Page", "You are already on the first page!");
        return;
    } else {
        int currentPage = imageloader.getCurrentPage() - 1;
        imageloader.setCurrentPage(currentPage);
        ui->pageLabel->setText(QString::number(currentPage+1) + "/" + QString::number(imageloader.getLength()));
        QPixmap pic(imageloader.getPage(imageloader.getCurrentPage()));
        ui->pageDisplay->setPixmap(pic.scaled(ui->pageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::on_pageJumpButton_clicked()
{
    if(ui->pageJumpLineEdit->text().toInt() < 1){
        QMessageBox::critical(this, "Page out of range", "Page number must be greater than zero!");
        return;
    } else if(ui->pageJumpLineEdit->text().toInt() > imageloader.getLength() - 1){
        QMessageBox::information(this, "Page out of range", "Page number must be less than or equal to" +
                                 QString::number(imageloader.getLength()));
    } else {
        int currentPage = ui->pageJumpLineEdit->text().toInt() - 1;
        imageloader.setCurrentPage(currentPage);
        ui->pageLabel->setText(QString::number(currentPage+1) + "/" + QString::number(imageloader.getLength()));
        QPixmap pic(imageloader.getPage(imageloader.getCurrentPage()));
        ui->pageDisplay->setPixmap(pic.scaled(ui->pageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
