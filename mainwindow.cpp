#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageloader.h"
#include <QPixmap>
#include <QMessageBox>
#include <qDebug>
#include <QFileDialog>
// /Users/admin/Desktop/testManga

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pageDisplay->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->pageDisplay->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    QWidget::showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImageForPage()
{
    scene->clear();
    scene->addPixmap(imageloader.getPage(imageloader.getCurrentPage()));
    scene->setSceneRect(0, 0, imageloader.getPage(imageloader.getCurrentPage()).width(),
                       imageloader.getPage(imageloader.getCurrentPage()).height());
    ui->pageDisplay->setScene(scene);
}

void MainWindow::on_getMangaButton_clicked()
{

    imageloader.loadBook(QFileDialog::getExistingDirectory());
    imageloader.setCurrentPage(0);
    ui->pageLabel->setText("1/" + QString::number(imageloader.getLength()));
    this->setImageForPage();
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
        this->setImageForPage();
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
        this->setImageForPage();
    }
}

void MainWindow::on_pageJumpButton_clicked()
{
    if(ui->pageJumpLineEdit->text().toInt() < 1){
        QMessageBox::critical(this, "Page out of range", "Page number must be greater than zero!");
        return;
    } else if(ui->pageJumpLineEdit->text().toInt() > imageloader.getLength() - 1){
        QMessageBox::information(this, "Page out of range", "Page number must be less than or equal to " +
                                 QString::number(imageloader.getLength()));
    } else {
        int currentPage = ui->pageJumpLineEdit->text().toInt() - 1;
        imageloader.setCurrentPage(currentPage);
        ui->pageLabel->setText(QString::number(currentPage+1) + "/" + QString::number(imageloader.getLength()));
        this->setImageForPage();
    }
}

void MainWindow::on_zoomInButton_clicked()
{
    imageloader.increaseScaleFactor();
    this->setImageForPage();
}

void MainWindow::on_zoomOutButton_clicked()
{
    imageloader.decreaseScaleFactor();
    this->setImageForPage();
}

void MainWindow::on_zoomResetButton_clicked()
{
    imageloader.setScaleFactor(1);
    this->setImageForPage();
}

void MainWindow::on_firstPageButton_clicked()
{
    imageloader.setCurrentPage(0);
    ui->pageLabel->setText("0/" + QString::number(imageloader.getLength()));
    this->setImageForPage();
}

void MainWindow::on_lastPageButton_clicked()
{
    imageloader.setCurrentPage(imageloader.getLength() - 1);
    ui->pageLabel->setText(QString::number(imageloader.getLength()) + "/" + QString::number(imageloader.getLength()));
    this->setImageForPage();
}
